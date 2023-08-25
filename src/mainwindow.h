#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "squirrellinter.h"
#include "level.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    SquirrelLinter m_linter;

    Level* m_level;
};
#endif // MAINWINDOW_H
