#ifndef SPRITEMODEL_H
#define SPRITEMODEL_H

#include <sprite/sprite.hpp>
#include <util/reader_document.hpp>
#include <util/reader_mapping.hpp>
#include <video/surface.hpp>
#include <video/surface_ptr.hpp>

#include <QAbstractListModel>
#include <QDir>
#include <QUrl>
#include <QtQml>

class SpriteModel : public QAbstractListModel {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QUrl spriteFile
               READ spriteFile
               WRITE setSpriteFile
               NOTIFY spriteFileChanged)

public:
    enum ActionRoles {
        FramesRole = Qt::UserRole,
        BidirectionalRole = Qt::UserRole + 1,
        FpsRole = Qt::UserRole + 2
    };

    explicit SpriteModel(QObject* parent = nullptr);

    inline QUrl spriteFile() { return m_spriteFile; }
    void setSpriteFile(QUrl url);

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int, QByteArray> roleNames() const override;

signals:
    void spriteFileChanged();

private:
    QUrl m_spriteFile;
    SpriteData* m_sprite = nullptr;

};

#endif // SPRITEMODEL_H
