#include "projectmodel.h"

IProjectModel::IProjectModel(QAbstractItemModel *mod) {
    m_model = mod;
}

QHash<int, QByteArray> IProjectModel::roleNames() const {
    QHash<int, QByteArray> out;

    out[Qt::DisplayRole] = "display"; // Not to be confused with content
    out[Qt::EditRole] = "edit";
    out[Qt::DecorationRole] = "decoration";
    out[Qt::ToolTipRole] = "tooltip";

    out[TypeRole] = "type";
    out[ContentRole] = "content";

    return out;
}
