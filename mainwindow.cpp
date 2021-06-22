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

    };

    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTitle(QString theme)
{
    ui->current_joke->setText(theme);
}


void MainWindow::showJoke() {
    if (this->hasPlayerSmiled) {

    }
    ui->current_joke->setText(this->jokesList[this->nextRoundIndex]);
}

void MainWindow::showTheme() {
    ui->current_theme->setText("Th�me: " + this->chosenTheme);
}

void MainWindow::showJokeIndex() {
    QString jokesPassed = QString::number(this->nextRoundIndex);
    ui->joke_counter->setText(jokesPassed);
}

void MainWindow::startGame() {
    //this->setQuestionList();
    this->nextRoundIndex = 0;
    this->hasPlayerSmiled = false;
    this->nextRound();
}

void MainWindow::startRound() {
    this->showJoke();
    this->nextRoundIndex += 1;
    this->startTimer();

};


void MainWindow::startTimer() {
    int CountDown = this->roundDuration;
    std::thread timerThread(&MainWindow::countDown, this);

    timerThread.detach();
}

void MainWindow::setChosenTheme(QString theme) {
    this->chosenTheme = theme;
}

void MainWindow::setMultiplayerMode(bool multiplayer) {
    this->isMultiplayerMode = multiplayer;
    if (multiplayer == true) {
        this->playerCount = 2;
    }
    else {
        this->playerCount = 1;
    }
}

void MainWindow::setHasPlayerSmiled(bool playerSmiled) {
    this->hasPlayerSmiled = playerSmiled;
};

void MainWindow::countDown() {
    this->hasPlayerSmiled = false;
    std::this_thread::sleep_for(std::chrono::seconds(8)); //this->roundDuration
    if (this->hasPlayerSmiled) {
        qInfo() << "END GAME";
        //this->endGame();
    }
    else {
        qInfo() << "NEXT ROUND";
        this->nextRound();
    }
}

void MainWindow::nextRound() {
    this->changeJokeCounter();
    if (this->hasPlayerSmiled == true) {
        qInfo() << "SMILE";
    }
    if (this->nextRoundIndex == 10 ) {
        qInfo() << "END GAME";
    }
    else {
        this->startRound();

    }
};

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

void MainWindow::on_back_to_menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_button_exit_clicked()
{
    close();
    this->CloseGame = true;
}