#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Rect_triggered()
{
    ui->openGLWidget->drawShape(LXBOpenGLWidget::Rect);
}


void MainWindow::on_Clear_triggered()
{
    ui->openGLWidget->drawShape(LXBOpenGLWidget::None);
}

void MainWindow::on_actWireframe_triggered()
{
    ui->openGLWidget->setWireframe(ui->actWireframe->isChecked());
}

