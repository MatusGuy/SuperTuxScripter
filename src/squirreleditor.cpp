#include "squirreleditor.h"

SquirrelEditor::SquirrelEditor(QWidget* parent): QTextEdit(parent), m_highlighter(document()) {
    setFontFamily("Consolas");
    setAcceptRichText(false);
    setTabStopDistance(8*4);
}
