#include "levelscriptsmodel.h"

LevelScriptsModel::LevelScriptsModel(QObject *parent): QStandardItemModel(parent) {
    connect(
        &SuperTuxThread::instance(), &SuperTuxThread::started,
        this, &LevelScriptsModel::refreshLevel
    );
}

void LevelScriptsModel::setLevelFileName(const QString& level) {
    m_levelFileName = level;
    emit levelFileNameChanged();

    if (SuperTuxThread::instance().isRunning())
        refreshLevel();
}

void LevelScriptsModel::refreshLevel() {
    if (m_levelFileName.isEmpty()) {
        m_level.reset(); // Die
        QStandardItemModel::clear();
        return;
    }

    if (!ScreenManager::current()) return;

    ScreenManager::current()->push_screen(std::make_unique<Editor>());
    Editor::current()->set_level(m_levelFileName.toStdString());
    while (!Editor::current()->get_level()) QThread::msleep(50);
    m_level.reset(Editor::current()->get_level());
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

            int srow = 0;
            ObjectSettings settings = object->get_settings();

            for (const std::unique_ptr<ObjectOption>& opt : settings.get_options()) {
                if (opt->get_flags() & ObjectOptionFlag::OPTION_HIDDEN) continue;
                if (opt->get_key().find("script") == std::string::npos) continue;
                objitem->setChild(srow, newItem(ScriptType, QString::fromStdString(opt->get_text()), object->get_type()));
                srow++;
            }

            row++;
        }
    }
}

QStandardItem* LevelScriptsModel::newItem(Level* obj) {
    auto item = new QStandardItem(qstdstr(obj->get_name()));
    item->setData(LevelType);
    item->setData("globe", Qt::DecorationRole);
    return item;
}

QStandardItem* LevelScriptsModel::newItem(Sector* obj) {
    auto item = new QStandardItem(qstdstr(obj->get_name()));
    item->setData(SectorType);
    item->setData("forest", Qt::DecorationRole);
    return item;
}

QStandardItem* LevelScriptsModel::newItem(TileMap* obj) {
    auto item = new QStandardItem(
        !obj->get_name().empty() ? qstdstr(obj->get_name()) :
        QString::number(obj->get_layer())
    );
    item->setData(TilemapType);
    item->setData("grid", Qt::DecorationRole);
    return item;
}

QStandardItem* LevelScriptsModel::newItem(GameObject* obj) {
    auto item = new QStandardItem(
        !obj->get_name().empty() ? qstdstr(obj->get_name()) :
        QString("<unnamed %1>").arg(qstdstr(obj->get_display_name()))
    );
    item->setData(GameObjectType);
    item->setData("object", Qt::DecorationRole);
    return item;
}

QStandardItem* LevelScriptsModel::newItem(ObjectType type, const QString& name, const QVariant& value) {
    auto item = new QStandardItem(name);
    item->setData(type);
    item->setData("code", Qt::DecorationRole);
    return item;
}
