#ifndef PROJECTSMODEL_H
#define PROJECTSMODEL_H

#include <QConcatenateTablesProxyModel>
#include <QQmlEngine>

#include "projectmodel.h"

class ProjectsModel : public QConcatenateTablesProxyModel {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ProjectsModel(QObject *parent = nullptr);

    Q_INVOKABLE void addProject(IProjectModel* proj);
    Q_INVOKABLE void removeProject(IProjectModel* proj);
};

#endif // PROJECTSMODEL_H
