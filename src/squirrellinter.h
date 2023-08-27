#ifndef SQUIRRELLINTER_H
#define SQUIRRELLINTER_H

#include <QObject>

#include <squirrel.h>
#include <sqconfig.h>

class SquirrelLinter : public QObject {
    Q_OBJECT

public:
    explicit SquirrelLinter(QObject *parent = nullptr);
    ~SquirrelLinter();

    void lint(const QString& code);

signals:
    void errored(const QString& msg, int line);

private:
    HSQUIRRELVM m_vm;

};

#endif // SQUIRRELLINTER_H
