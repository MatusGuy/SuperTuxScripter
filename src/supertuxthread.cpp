#include "supertuxthread.h"

SuperTuxThread::SuperTuxThread(QObject *parent): QThread{parent} {
    setPriority(Priority::NormalPriority);
}

SuperTuxThread::~SuperTuxThread() {
    if (m_main) stop();
}

void SuperTuxThread::start() {
    m_main = new Main;
    QThread::start();
}

void SuperTuxThread::stop() {
    Q_ASSERT(m_main);
    //TODO: Invoke quit event
    delete m_main; m_main = nullptr;
}

void SuperTuxThread::waitForGame() {

    if (!m_main) return; // ooo ma gawwd

    // I don't care if this goes on infinitely
    while (!ScreenManager::current()) QThread::msleep(50);

    while (ScreenManager::current()->get_screen_stack().size() == 0) {
        QThread::msleep(50);
    }
}

void SuperTuxThread::run() {
    char* argv[] = {"supertux2"};
    m_main->run(1, argv);

}
