#include "squirrelhighlighter.h"

SquirrelHighlighter::SquirrelHighlighter(QQuickTextDocument* doc):
    QuickSyntaxHighlighter(doc),
    m_normal_format(".*", QColor(Qt::black), QFont::Normal)
{
    std::reverse(std::begin(m_blocks), std::end(m_blocks));

    connect(
        this, &SquirrelHighlighter::textDocumentChanged,
        this, [this](){
            // put that stupid tab size to 4
            QTextOption opt = document()->defaultTextOption();
            opt.setTabStopDistance(0);
            document()->setDefaultTextOption(opt);
        }
    );
}

void SquirrelHighlighter::highlightBlock(const QString& text) {
    setFormat(0,text.length(),m_normal_format.format);

    for (const HighlightBlock &block : m_blocks) {
        QRegularExpressionMatchIterator i = block.regex.globalMatch(text);
        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            if (match.hasMatch()) setFormat(match.capturedStart(), match.capturedLength(), block.format);
        }
    }

    // highlight multiline comments
    QRegularExpressionMatchIterator i = m_blocks[4].regex.globalMatch(document()->toPlainText());
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if (match.hasMatch()) setFormat(match.capturedStart(), match.capturedLength(), m_blocks[4].format);
    }
}

HighlightBlock::HighlightBlock(
    const QString& exp,
    QColor color,
    QFont::Weight weight
): regex(exp, QRegularExpression::DotMatchesEverythingOption | QRegularExpression::MultilineOption) {
    qDebug() << exp << "- pattern options:" << regex.patternOptions();
    format.setForeground(color);
    format.setFontWeight(weight);
    format.setFontFamilies(QStringList("Consolas"));
}
