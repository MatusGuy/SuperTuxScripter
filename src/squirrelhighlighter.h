#ifndef SQUIRRELHIGHLIGHTER_H
#define SQUIRRELHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QStringList>
#include <QRegularExpressionMatchIterator>
#include <QQuickTextDocument>
#include <QtQml>

#include <array>

struct HighlightBlock {
    HighlightBlock(const QString& exp, QColor color, QFont::Weight weight);

    QRegularExpression regex;
    QTextCharFormat format;
};

class QuickSyntaxHighlighter : public QSyntaxHighlighter {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(
        QQuickTextDocument* textDocument
        READ textDocument
        WRITE setTextDocument
        NOTIFY textDocumentChanged
        REQUIRED
    )

public:
    QuickSyntaxHighlighter(QQuickTextDocument* doc = nullptr): QSyntaxHighlighter((QTextDocument*) nullptr) {
        setTextDocument(doc);
    }

    inline QQuickTextDocument* textDocument() {
        return m_doc;
    }

    inline void setTextDocument(QQuickTextDocument* doc) {
        m_doc = doc;
        setDocument(doc != nullptr ? doc->textDocument() : nullptr);
        emit textDocumentChanged(m_doc);
    }

signals:
    void textDocumentChanged(QQuickTextDocument*);

private:
    QQuickTextDocument* m_doc;
};

class SquirrelHighlighter : public QuickSyntaxHighlighter {
    Q_OBJECT
    QML_ELEMENT

public:
    SquirrelHighlighter(QQuickTextDocument* doc = nullptr);

    // QSyntaxHighlighter interface
protected:
    void highlightBlock(const QString& text);

private:
    HighlightBlock m_normal_format;
    std::array<HighlightBlock,5> m_blocks = {
        HighlightBlock(R"(((//|#).*|/\*(.*?)\*/))", QColor(Qt::gray), QFont::Normal),
        HighlightBlock(R"(".*")", QColor(Qt::darkYellow), QFont::Normal),
        HighlightBlock(R"((0(x|b))?\d+)", QColor(Qt::green), QFont::Normal),
        HighlightBlock(R"(\b(base|break|case|catch|class|clone|con(tinue|st(ructor)?)|default|delete|else|enum|extends|for|foreach|function|if|in|local|null|resume|return|switch|this|throw|try|typeof|while|yield|instanceof|true|false|static|__LINE__|__FILE__|rawcall)\b)", QColor(Qt::darkCyan), QFont::Bold),
        HighlightBlock(R"(\w+(?=\())", QColor(Qt::magenta), QFont::Normal)
    };
};

#endif // SQUIRRELHIGHLIGHTER_H
