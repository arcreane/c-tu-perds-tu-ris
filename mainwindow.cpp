#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QString>
#include <QtCore>
#include <QCoreApplication.h>
#include "Game.h"
#include <QDebug>
#include <string>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <QFrame>
#include <QObject>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    {

        /*       connect(&game, &Game::closeGame, &a, &QCoreApplication::quit, Qt::QueuedConnection);*/
    };
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showJoke() {
    ui->current_joke->setText(this->jokesList[this->nextRoundIndex]);
}

void MainWindow::showTheme() {
    ui->current_theme->setText("Thème: " + this->chosenTheme);
}

void MainWindow::showJokeIndex() {
    QString jokesPassed = QString::number(this->nextRoundIndex);
    ui->joke_counter->setText(jokesPassed);
}

void MainWindow::changeJokeCounter() {
    QString jokesPassed = QString::number(this->nextRoundIndex);
    ui->joke_counter->setText(jokesPassed);
    ui->joke_counter_2->setText(jokesPassed);
}


void MainWindow::endGame(){
    if (this->hasPlayerSmiled) {
        ui->stackedWidget->setCurrentIndex(3);
    }
    else {
        ui->stackedWidget->setCurrentIndex(4);
    }
};

void MainWindow::on_button_single_mode_clicked()
{
    this->setMultiplayerMode(false);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_button_multiplayer_mode_clicked()
{
    this->setMultiplayerMode(true);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_button_toto_theme_clicked(QString theme)
{
    this->setChosenTheme(theme);
    ui->current_theme->setText(this->chosenTheme);
    ui->current_theme_2->setText(this->chosenTheme);
    ui->stackedWidget->setCurrentIndex(2);
    this->startGame();
}
void MainWindow::on_button_computer_theme_clicked(QString theme)
{
    this->setChosenTheme(theme);
    ui->current_theme->setText(this->chosenTheme);
    ui->current_theme_2->setText(this->chosenTheme);
    ui->stackedWidget->setCurrentIndex(2);
    this->startGame();
}
void MainWindow::on_button_political_theme_clicked(QString theme)
{
    this->setChosenTheme(theme);
    ui->current_theme->setText(this->chosenTheme);
    ui->current_theme_2->setText(this->chosenTheme);
    ui->stackedWidget->setCurrentIndex(2);
    this->startGame();
}
void MainWindow::on_button_boring_theme_clicked(QString theme)
{
    this->setChosenTheme(theme);
    ui->current_theme->setText(this->chosenTheme);
    ui->current_theme_2->setText(this->chosenTheme);
    ui->stackedWidget->setCurrentIndex(2);
    this->startGame();
}
void MainWindow::on_button_teacher_theme_clicked(QString theme)
{
    this->setChosenTheme(theme);
    ui->current_theme->setText(this->chosenTheme);
    ui->current_theme_2->setText(this->chosenTheme);
    ui->stackedWidget->setCurrentIndex(2);
    this->startGame();
}
void MainWindow::on_button_all_theme_clicked(QString theme)
{
    this->setChosenTheme(theme);
    ui->current_theme->setText(this->chosenTheme);
    ui->current_theme_2->setText(this->chosenTheme);
    ui->stackedWidget->setCurrentIndex(2);
    this->startGame();
}


void MainWindow::on_replay_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
};
void MainWindow::on_main_menu_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
};
