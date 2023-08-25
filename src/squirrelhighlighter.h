#ifndef SQUIRRELHIGHLIGHTER_H
#define SQUIRRELHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QStringList>
#include <QRegularExpressionMatchIterator>
#include <array>

struct HighlightBlock {
    HighlightBlock(const QString& exp, QColor color, QFont::Weight weight);

    QRegularExpression regex;
    QTextCharFormat format;
};

class SquirrelHighlighter : public QSyntaxHighlighter {
public:
    SquirrelHighlighter(QTextDocument* parent);

    // QSyntaxHighlighter interface
protected:
    void highlightBlock(const QString& text);

private:
    HighlightBlock m_normal_format;
    std::array<HighlightBlock,5> m_blocks = {
        HighlightBlock(R"(((//|#).*|/\*(.*?)\*/))", QColor(Qt::gray), QFont::Normal),
        HighlightBlock(R"(".*")", QColor(Qt::yellow), QFont::Normal),
        HighlightBlock(R"((0(x|b))?\d+)", QColor(Qt::green), QFont::Normal),
        HighlightBlock(R"(\b(base|break|case|catch|class|clone|con(tinue|st(ructor)?)|default|delete|else|enum|extends|for|foreach|function|if|in|local|null|resume|return|switch|this|throw|try|typeof|while|yield|instanceof|true|false|static|__LINE__|__FILE__|rawcall)\b)", QColor(Qt::cyan), QFont::Bold),
        HighlightBlock(R"(\w+(?=\())", QColor(Qt::magenta), QFont::Normal)
    };
};

#endif // SQUIRRELHIGHLIGHTER_H
