#include "projectsmodel.h"

ProjectsModel::ProjectsModel(QObject* parent):
    QConcatenateTablesProxyModel{parent}
{
}

void ProjectsModel::addProject(IProjectModel* proj) {
    addSourceModel(proj->model());
}

void ProjectsModel::removeProject(IProjectModel* proj) {
    removeSourceModel(proj->model());
}
