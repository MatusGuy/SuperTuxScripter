#ifndef LEVELSCRIPTSMODEL_H
#define LEVELSCRIPTSMODEL_H

#include <memory>

#include <supertux/screen_manager.hpp>
#include <supertux/level_parser.hpp>
#include <supertux/level.hpp>
#include <supertux/sector.hpp>
#include <supertux/game_object.hpp>
#include <object/tilemap.hpp>

#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QtQml>

#define qstdstr QString::fromStdString

class QuickFileSystemModel : public QFileSystemModel {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath NOTIFY rootPathChanged)

signals:
    void rootPathChanged();

};

// I do know QAbstractItemModel is faster but I just
// can't wrap my head around it!!!
class LevelScriptsModel : public QStandardItemModel {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString levelFileName READ levelFileName WRITE setLevelFileName NOTIFY levelFileNameChanged)

public:
    explicit LevelScriptsModel(QObject *parent = nullptr);

    enum ObjectType : int {
        LevelType = 0,
        SectorType = 1,
        TilemapType = 2,
        GameObjectType = 3,
        ScriptType = 4
    };

    union GameObjectNode {
        ObjectType type;
        QString name;

        GameObjectNode* parent = nullptr;
        std::vector<GameObjectNode> children;
    };

    inline QString levelFileName() { return m_levelFileName; }
    void setLevelFileName(const QString& level);

    void refreshLevel();

    QStandardItem* newItem(Level* obj);
    QStandardItem* newItem(Sector* obj);
    QStandardItem* newItem(TileMap* obj);
    QStandardItem* newItem(GameObject* obj);
    QStandardItem* newItem(ObjectType type, const QString& name, const QVariant& value);

signals:
    void levelFileNameChanged();

private:
    QString m_levelFileName;
    std::unique_ptr<Level> m_level;
};

#endif // LEVELSCRIPTSMODEL_H
