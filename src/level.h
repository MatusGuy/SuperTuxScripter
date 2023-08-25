#ifndef LEVEL_H
#define LEVEL_H

#include <sexp/parser.hpp>
#include <string>

#include <QDebug>
#include <QFile>

struct LevelMetadata {
    int version;
    QString name;
    QString author;
    QString license;
};

class Level : public QFile {
public:
    Level(const QString& path);
    ~Level();

    inline LevelMetadata& levelMetadata() { return m_level_metadata; }

    void setLevelSize(const QSize& size);

private:
    LevelMetadata m_level_metadata;

    sexp::Value m_sexp;
};

#endif // LEVEL_H
