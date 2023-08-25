#ifndef SQUIRRELEDITOR_H
#define SQUIRRELEDITOR_H

#include <QTextEdit>
#include <QFontMetrics>

#include "squirrelhighlighter.h"

class SquirrelEditor : public QTextEdit {
public:
    SquirrelEditor(QWidget* parent);

private:
    SquirrelHighlighter m_highlighter;
};

#endif // SQUIRRELEDITOR_H
