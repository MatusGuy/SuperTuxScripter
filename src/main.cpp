#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickStyle>

#include "squirrelhighlighter.h"

const QUrl g_url(u"qrc:/qml/MainWindow.qml"_qs);

void onObjectCreated(QObject *obj, const QUrl &objUrl) {
    if (!obj && g_url == objUrl) QCoreApplication::exit(-1);
}

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    app.setApplicationName("SuperTuxScripter");

    QQmlApplicationEngine engine;

    qmlRegisterType<QuickSyntaxHighlighter>("Code", 1, 0, "SyntaxHighlighter");

    qmlRegisterType<SquirrelHighlighter>("Squirrel", 1, 0, "SquirrelHighlighter");

    QQuickStyle::setStyle("Material");
    QQuickWindow::setTextRenderType(QQuickWindow::NativeTextRendering);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, &onObjectCreated,
                     Qt::QueuedConnection
                     );
    engine.load(g_url);


    return app.exec();
}
