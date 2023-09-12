#ifndef LEVELSCRIPTSMODEL_H
#define LEVELSCRIPTSMODEL_H

#include <memory>

#include <editor/editor.hpp>
#include <supertux/screen_fade.hpp>
#include <supertux/screen_manager.hpp>
#include <supertux/level_parser.hpp>
#include <supertux/level.hpp>
#include <supertux/sector.hpp>
#include <supertux/game_object.hpp>
#include <object/tilemap.hpp>

#include "supertuxthread.h"

#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QRegularExpression>
#include <QtQml>

#define qstdstr QString::fromStdString

class QuickFileSystemModel : public QFileSystemModel {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath NOTIFY rootPathChanged)

private:
    QHash<QString, QString> iconmap = {
        {".nut", "code"}
    };

public:
    QVariant data(const QModelIndex &index, int role) const override {
        switch (role) {

        case Qt::ToolTipRole:
            return QFileSystemModel::data(index, QFileSystemModel::FilePathRole);

        case Qt::DecorationRole: {
            QFileInfo filepath(data(index, QFileSystemModel::FilePathRole).toString());

#ifdef Q_OS_LINUX
            if (filepath.isRoot() || filepath.absoluteFilePath() == "/mnt/") return "drive";
#endif
            if (filepath.isDir()) return "folder";

            QString suffix = filepath.suffix();
            const auto& it = iconmap.find(suffix);

            // Ok Qt... Whatever you say.
            while (it != iconmap.end() && it.key() == suffix) return it.value();

            return "file";
        }

        default:
            return QFileSystemModel::data(index, role);
        };
    }

    QHash<int, QByteArray> roleNames() const override {
        auto resp = QFileSystemModel::roleNames();
        resp[Qt::DecorationRole] = "decoration";
        resp[Qt::ToolTipRole] = "toolTip";
        return resp;
    }

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
