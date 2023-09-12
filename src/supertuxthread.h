#ifndef SUPERTUXTHREAD_H
#define SUPERTUXTHREAD_H

#include <cstdarg>

#include "singleton.h"

#include <supertux/main.hpp>
#include <supertux/screen_fade.hpp>
#include <supertux/screen_manager.hpp>

#include <QThread>
#include <QEventLoop>
#include <QtQml>

class SuperTuxThread : public QThread, public Singleton<SuperTuxThread> {
    Q_OBJECT
    QML_SINGLETON

public:
    Q_INVOKABLE void startSuperTux();
    Q_INVOKABLE void quitSuperTux();
    Q_INVOKABLE bool isRunning() { return QThread::isRunning(); }

    void waitForGame();

    static char** toArgv(size_t sz, ...);

protected:
    void run();

private:

    Main* m_main = nullptr;

};

#endif // SUPERTUXTHREAD_H
