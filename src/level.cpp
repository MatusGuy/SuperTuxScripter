#include "level.h"

Level::Level(const QString& path): QFile(path) {
    return;

    if (!open(QIODevice::ReadOnly)) {
        qFatal() << "Error opening file:" << errorString() << error();
    }

    m_sexp = sexp::Parser::from_string(readAll().toStdString());
    if (m_sexp.get_car().str() != "supertux-level") {
        qFatal() << "Not a supertux level";
    }

    sexp::Value& level = m_sexp.get_cdr();
    QStringList metadataKeys;
    metadataKeys << "version" << "name" << "author" << "license";
    for (const sexp::Value& key : level.get_cdr().as_array()) {
        switch (0) {
        case 0:
            m_level_metadata.version = key.get_cdr().as_int();
            break;

        case 1:
            // (name (_ "helloo"))
            // something related to translation?
            // idk why one would translate a level name
            m_level_metadata.name = key.get_cdr().get_cdr().as_string().c_str();
            break;

        case 3:
            m_level_metadata.author = key.get_cdr().as_string().c_str();
            break;

        case 4:
            m_level_metadata.license = key.get_cdr().as_string().c_str();
            break;
        }
    }
}

Level::~Level() {

}

void Level::setLevelSize(const QSize& size) {

}
