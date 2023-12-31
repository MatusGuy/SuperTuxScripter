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
#include "projectmodel.h"

#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QRegularExpression>
#include <QtQml>

#define qstdstr QString::fromStdString

class QuickFileSystemModel : public QFileSystemModel, public IProjectModel {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath NOTIFY rootPathChanged)

private:
    QHash<QString, QString> iconmap = {
        {".nut", "code"}
    };

public:
    explicit QuickFileSystemModel(QObject* parent = nullptr):
        QFileSystemModel(parent),
        IProjectModel(this)
    {}

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

            QString iconname = iconmap.value(filepath.suffix(), "");

            return iconname.isEmpty() ? "file" : iconname;
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
class LevelScriptsModel : public QStandardItemModel, public IProjectModel {
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

    virtual QHash<int, QByteArray> roleNames() const override;

signals:
    void levelFileNameChanged();

private:
    QString m_levelFileName;
    std::unique_ptr<Level> m_level;
};

#endif // LEVELSCRIPTSMODEL_H
