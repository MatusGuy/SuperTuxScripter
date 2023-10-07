#ifndef IPROJECTMODEL_H
#define IPROJECTMODEL_H

#include <QAbstractItemModel>
#include <QtQml>

namespace Project {
    Q_NAMESPACE

    enum ItemType {
        GENERIC,
        SCRIPT
    };
    Q_ENUM_NS(ItemType)

}

/** Not a true interface... :) */
class IProjectModel {
public:
    explicit IProjectModel(QAbstractItemModel* mod = nullptr);

    enum ItemRole {
        TypeRole = Qt::UserRole,
        ContentRole,

        CustomRole
    };

    virtual QHash<int, QByteArray> roleNames() const;

    // Composition > inheritance in this case... I think
    inline void setModel(QAbstractItemModel* mod) { m_model = mod; }
    inline QAbstractItemModel* model() { return m_model; }

private:
    QAbstractItemModel* m_model = nullptr;
};

#endif // IPROJECTMODEL_H
