#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_single_mode_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_button_multiplayer_mode_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

