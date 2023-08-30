#include <QGuiApplication>
#include <QFileSystemModel>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickStyle>
#include <QPalette>

// This is a Qt macro
#undef foreach
// In modern days, it's useless, but I don't mind that
// Sadly, it interferes with tinygettext
// Farewell.

#define SDL_MAIN_HANDLED
#include <supertux/main.hpp>

#include "squirrelhighlighter.h"
#include "levelscriptsmodel.h"

const QUrl g_url(u"qrc:/qml/MainWindow.qml"_qs);

void onObjectCreated(QObject *obj, const QUrl &objUrl) {
    if (!obj && g_url == objUrl) QCoreApplication::exit(-1);
}

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    app.setApplicationName("SuperTuxScripter");

    QQmlApplicationEngine engine;

    qmlRegisterType<QuickFileSystemModel>("Code", 1, 0, "FileSystemModel");
    qmlRegisterType<QuickSyntaxHighlighter>("Code", 1, 0, "SyntaxHighlighter");

    qmlRegisterType<SquirrelHighlighter>("Squirrel", 1, 0, "SquirrelHighlighter");

    qmlRegisterType<LevelScriptsModel>("SuperTux", 1, 0, "LevelScriptsModel");

    QQuickStyle::setStyle("Basic");
    QQuickWindow::setTextRenderType(QQuickWindow::NativeTextRendering);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, &onObjectCreated,
                     Qt::QueuedConnection
                     );
    engine.load(g_url);


    return app.exec();
}
