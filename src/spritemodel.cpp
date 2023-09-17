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
            endResetModel();
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

    return createIndex(row, column, static_cast<void*>(action));
}

int SpriteModel::rowCount(const QModelIndex &parent) const {
    if (!m_sprite) return 0;
    return static_cast<int>(m_sprite->get_actions().size());
}

QVariant SpriteModel::data(const QModelIndex &index, int role) const {
    if (!m_sprite || !index.internalPointer()) return QVariant();

    if (role == Qt::EditRole) role = Qt::DisplayRole;

    auto action = static_cast<SpriteData::Action*>(index.internalPointer());

    if (!action) return QVariant();

    switch (role) {
        case Qt::DisplayRole: return QString::fromStdString(action->name);

        case Qt::DecorationRole: {
            SurfacePtr surface = action->surfaces[0];
            return QUrl(QString("file:///mnt/data/Games/SuperTux/data/").append(surface->get_filename()));
        }

        case FramesRole: {
            std::vector<SurfacePtr>& surfaces = action->surfaces;
            QVariantList frames;

            for (SurfacePtr& surface : surfaces) {
                frames.append(QUrl(QString("file:///mnt/data/Games/SuperTux/data/").append(surface->get_filename())));
            }

            return frames;
        }

        case BidirectionalRole: return false; // TODO: Implement me!

        case FpsRole: return action->fps;
    }

    return QVariant();
}

bool SpriteModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (data(index, role) == value) return false;

    // FIXME: Implement me!
    emit dataChanged(index, index, {role});
    return true;
}

Qt::ItemFlags SpriteModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::NoItemFlags;

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

    map[FramesRole] = "frames";
    map[BidirectionalRole] = "isBidirectional";
    map[FpsRole] = "fps";

    return map;
}
