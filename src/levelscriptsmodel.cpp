#include "levelscriptsmodel.h"

LevelScriptsModel::LevelScriptsModel(QObject *parent): QStandardItemModel(parent) {

}

void LevelScriptsModel::setLevelFileName(const QString& level) {
    m_levelFileName = level;
    emit levelFileNameChanged();
    refreshLevel();
}

void LevelScriptsModel::refreshLevel() {
    if (m_levelFileName.isEmpty()) {
        m_level.reset(); // Die
        clear();
        return;
    }

    if (!ScreenManager::current()) return;

    m_level = LevelParser::from_file(m_levelFileName.toStdString(), false, true);
    auto levelitem = newItem(m_level.get());
    setItem(0, levelitem);

    for (size_t i = 0; i < m_level->get_sector_count(); i++) {
        Sector* sector = m_level->get_sector(i);
        auto sectoritem = newItem(sector);
        levelitem->setChild(i, sectoritem);

        int row = 0;
        for (TileMap* tilemap : sector->get_all_tilemaps()) {
            sectoritem->setChild(row, newItem(tilemap));
            row++;
        }

        for (const std::unique_ptr<GameObject>& object : sector->get_objects()) {
            if (object->get_name().empty()) continue;

            auto objitem = newItem(object.get());
            sectoritem->setChild(row, objitem);

            /*
            int srow = 0;
            for (ObjectOption* opt : object->get_settings().get_options()) {
                if (!dynamic_cast<ScriptObjectOption*>(opt)) continue; //segfault here
                objitem->setChild(srow, newItem(ScriptType, QString::fromStdString(opt->get_text()), object->get_type()));
                srow++;
            }
*/

            row++;
        }
    }
}

QStandardItem* LevelScriptsModel::newItem(Level* obj) {
    auto item = new QStandardItem(qstdstr(obj->get_name()));
    item->setData(LevelType);
    item->setIcon(QIcon(":/images/globe.svg"));
    return item;
}

QStandardItem* LevelScriptsModel::newItem(Sector* obj) {
    auto item = new QStandardItem(qstdstr(obj->get_name()));
    item->setData(SectorType);
    item->setIcon(QIcon(":/images/forest.svg"));
    return item;
}

QStandardItem* LevelScriptsModel::newItem(TileMap* obj) {
    auto item = new QStandardItem(
        !obj->get_name().empty() ? qstdstr(obj->get_name()) :
        QString::number(obj->get_layer())
    );
    item->setData(TilemapType);
    item->setIcon(QIcon(":/images/grid.svg"));
    return item;
}

QStandardItem* LevelScriptsModel::newItem(GameObject* obj) {
    auto item = new QStandardItem(
        !obj->get_name().empty() ? qstdstr(obj->get_name()) :
        QString("<unnamed %1>").arg(qstdstr(obj->get_display_name()))
    );
    item->setData(GameObjectType);
    item->setIcon(QIcon(":/images/object.svg"));
    return item;
}

QStandardItem* LevelScriptsModel::newItem(ObjectType type, const QString& name, const QVariant& value) {
    auto item = new QStandardItem(name);
    item->setData(type);
    item->setIcon(QIcon(":/images/code.svg"));
    return item;
}
