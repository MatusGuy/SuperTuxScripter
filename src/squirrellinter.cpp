#include "squirrellinter.h"

SquirrelLinter::SquirrelLinter(QObject *parent): QObject{parent} {
    m_vm = sq_open(1024);
}

SquirrelLinter::~SquirrelLinter() {
    sq_close(m_vm);
}

void SquirrelLinter::lint(const QString& code) {
    //SQRESULT resp = sq_compilebuffer(m_vm, code.toStdString().c_str(), (int) code.length(), "target", true);
    //if (SQ_FAILED(resp)) emit errored("nope", 0);
}
