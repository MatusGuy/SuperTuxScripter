#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_level = new Level(":/examples/level1.stl");
    m_level->setLevelSize(QSize(200,35));

    connect(
        ui->A_Compile, &QAction::triggered,
        this, [this](bool){
            m_linter.lint(ui->CodeEdit->toPlainText());
        }
    );
    connect(
        &m_linter, &SquirrelLinter::errored,
        this, [](const QString& msg, int line){
            qDebug() << msg << line;
        }
    );
}

MainWindow::~MainWindow() {
    delete m_level;
    delete ui;
}

