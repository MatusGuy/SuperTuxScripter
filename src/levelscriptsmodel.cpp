#include "levelscriptsmodel.h"

LevelScriptsModel::LevelScriptsModel(QObject *parent):
    QAbstractItemModel(parent)
{

}

QVariant LevelScriptsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    return QVariant();
}

QModelIndex LevelScriptsModel::index(int row, int column, const QModelIndex &parent) const {
    QModelIndex index = createIndex(row, column);
    return index;
}

QModelIndex LevelScriptsModel::parent(const QModelIndex &index) const {
    return QModelIndex();
}

int LevelScriptsModel::rowCount(const QModelIndex &parent) const {
    //if (!parent.isValid()) return 0;
    return 5;
}

int LevelScriptsModel::columnCount(const QModelIndex &parent) const {
    //if (!parent.isValid()) return 0;
    return 1;
}

QVariant LevelScriptsModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return "hello";
}


QHash<int, QByteArray> LevelScriptsModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[NameRole] = "name";
    return names;
}
