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

char** SuperTuxThread::toArgv(size_t sz, ...) {
    std::va_list args;
    int i;
    char **argv = (char**) std::malloc((sz+1) * sizeof(char*));
    char *temp;
    va_start(args, sz);
    for (i = 0; i < sz; i++) {
        temp = va_arg(args, char*);
        argv[i] = (char*) malloc(sizeof(temp+1));
        std::strcpy(argv[i],temp);
    }
    argv[i] = NULL;
    va_end(args);
    return argv;
}

void SuperTuxThread::run() {
    char** argv = toArgv(1, "supertux2");
    m_main->run(1, argv);
    std::free(argv);

}
