#ifndef SUPERTUXTHREAD_H
#define SUPERTUXTHREAD_H

#include <supertux/main.hpp>
#include <supertux/screen_manager.hpp>

#include <QThread>
#include <QEventLoop>

class SuperTuxThread : public QThread {
public:

    explicit SuperTuxThread(QObject *parent = nullptr);
    ~SuperTuxThread();

    void start();
    void stop();

    void waitForGame();

protected:
    void run();

private:

    Main* m_main = nullptr;

};

#endif // SUPERTUXTHREAD_H
