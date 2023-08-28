#ifndef LEVELSCRIPTSMODEL_H
#define LEVELSCRIPTSMODEL_H

#include <QAbstractItemModel>
#include <QtQml>

class LevelScriptsModel : public QAbstractItemModel {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit LevelScriptsModel(QObject *parent = nullptr);

    enum Role {
        NameRole = Qt::UserRole
    };

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

private:

};

#endif // LEVELSCRIPTSMODEL_H
