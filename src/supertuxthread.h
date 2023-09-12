#ifndef SUPERTUXTHREAD_H
#define SUPERTUXTHREAD_H

#include <cstdarg>

#include "singleton.h"

#include <supertux/main.hpp>
#include <supertux/screen_fade.hpp>
#include <supertux/screen_manager.hpp>

#include <QThread>
#include <QEventLoop>

class SuperTuxThread : public QThread, public Singleton<SuperTuxThread> {
public:
    void start();
    void stop();

    void waitForGame();

    static char** toArgv(size_t sz, ...);

protected:
    void run();

private:

    Main* m_main = nullptr;

};

#endif // SUPERTUXTHREAD_H
