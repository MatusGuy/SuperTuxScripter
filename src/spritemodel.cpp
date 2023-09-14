#include "spritemodel.h"

SpriteModel::SpriteModel(QObject* parent): QAbstractListModel(parent) {

}

void SpriteModel::setSpriteFile(QUrl url) {
    beginResetModel();
    QString path = url.toLocalFile();

    if (path.isEmpty()) {
        m_spriteFile = "";
        if (m_sprite) {
            delete m_sprite;
            m_sprite = nullptr;
        }
        return;
    }

    //TODO: system agnostic datadir
    QDir datadir("/mnt/data/Games/SuperTux/data/");
    auto doc = ReaderDocument::from_file(datadir.relativeFilePath(path).toStdString());
    ReaderMapping read(doc, doc.get_sexp());
    m_sprite = new SpriteData(read);

    endResetModel();
}

QModelIndex SpriteModel::index(int row, int column, const QModelIndex &parent) const {
    if (parent.isValid()) return QModelIndex();

    SpriteData::Actions::iterator it = m_sprite->get_actions().begin();
    std::advance(it, row);
    SpriteData::Action* action = it->second.get();

    return createIndex(row, column, (void*) action);
}

int SpriteModel::rowCount(const QModelIndex &parent) const {
    if (!m_sprite) return 0;
    return (int) m_sprite->get_actions().size();
}

QVariant SpriteModel::data(const QModelIndex &index, int role) const {
    if (!m_sprite) return QVariant();

    if (role == Qt::EditRole) role = Qt::DisplayRole;

    SpriteData::Actions::iterator it = m_sprite->get_actions().begin();
    std::advance(it, index.row());
    SpriteData::Action* action = it->second.get();

    switch (role) {
        case Qt::DisplayRole: return QString::fromStdString(action->name);
        case Qt::DecorationRole: {
            SurfacePtr surface = action->surfaces[0];
            return QUrl(QString::fromStdString(surface->get_filename()));
        }
    }

    return QVariant();
}

bool SpriteModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags SpriteModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

bool SpriteModel::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool SpriteModel::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> SpriteModel::roleNames() const {
    auto map = QAbstractListModel::roleNames();
    map[Qt::DisplayRole] = "display";
    map[Qt::DecorationRole] = "decoration";
    map[Qt::EditRole] = "edit";
    return map;
}
