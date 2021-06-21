#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtWidgets>
#include <chrono>
#include <thread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT


private:
	// Game Config
	int roundDuration = 3;
	int questionsPerPlayer = 10;
	QString jokesList[10] = {
		"Pourquoi les canards sont toujours a l'heure ? Parce qu'ils sont dans l'etang.",
		"Pourquoi n'y a-t-il pas de ballon sur le plateau de Questions Pour Un Champion ? Car Julien Lepers." ,
		"La maitresse a Toto : Cela suffit Toto, on ne joue pas en travaillant. Mais madame je ne travaille pas !",
		"Mais enfin toto, pourquoi te laves tu les mains avec des gants ? demande sa maman. Ben, pour ne pas salir le savon !",
		"Que dit un escargot quand il croise une limace ? Oh un naturiste.",
		"Quelle difference y a-t-il entre Windows et un clou ?  Aucune : tous deux sont destines a se planter.",
		"Savez-vous qui est Bob Marlex ? Euh Bah, c'est un chanteur de regex." ,
		"C'est une requete SQL qui entre dans un bar, et le serveur repond :  Il n'y a plus de tables !",
		"Que dit un escargot quand il croise une limace ? Oh un naturiste.",
		"C'est l'histoire d'un papier qui tombe à l'eau. Il crie : Au secours ! J'ai pas pied !"
	};
	
	// Predefined config
	int playerCount;
	int nextRoundIndex;
	QString chosenTheme;
	Ui::MainWindow* ui;
	bool didUserWin;
	bool isMultiplayerMode;
	bool hasPlayerSmiled = false;
	int currentCounter = 0;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool multiplayerMode() const { return this->isMultiplayerMode; }
	QString theme() const { return this->chosenTheme; }

	void startGame() {
		//this->setQuestionList();
		this->nextRoundIndex = 0;
		this->nextRound();
	}

	void nextRound() {
		this->changeJokeCounter();
 		if (this->nextRoundIndex == 10) {
			this->endGame();
		} else {
			this->startRound();
		}
	};



	void countDown() {
		this->hasPlayerSmiled = false;
		std::this_thread::sleep_for(std::chrono::seconds(8)); //this->roundDuration
		if (this->hasPlayerSmiled) {
			this->endGame();
			qInfo() << "END GAME";
		}
		else {
			qInfo() << "NEXT ROUND";
			this->nextRound();
		}
	}

	void startTimer() {
		int CountDown = this->roundDuration;
		std::thread timerThread(&MainWindow::countDown, this);
		timerThread.detach();
	}


	void startRound() {
		this->showJoke();
		this->nextRoundIndex += 1;
		this->startTimer();
	};


    //void setQuestionsList() {
    //    //get question list via API call
    //    QString fetchedQuestionList[10] = { "patate", "fromage", "raclette", "epinard", "foie gras", "spagetti", "tomates", "poisson", "crouton", "pain" };

    //    for (int i = 0; i < sizeof(this->jokesList); i++) {
    //        this->jokesList[i] = fetchedQuestionList[i];
    //    }
    //};


	void setHasPlayerSmiled(bool playerSmiled) {
		this->hasPlayerSmiled = playerSmiled;
	}


	void setChosenTheme(QString theme) {
		this->chosenTheme = theme;
	}

	void setMultiplayerMode(bool multiplayer) {
		this->isMultiplayerMode = multiplayer;
		if (multiplayer == true) {
			this->playerCount = 2;
		}
		else {
			this->playerCount = 1;
		}
	}


private slots:
	void showTheme();
	void showJoke();
	void changeJokeCounter();
	void showJokeIndex();
	void endGame();
    void on_button_single_mode_clicked();
    void on_button_multiplayer_mode_clicked();
	void on_replay_clicked();
	void on_main_menu_clicked();

	void on_button_toto_theme_clicked(QString theme = "TOTO");
	void on_button_computer_theme_clicked(QString theme = "INFORMATIQUE");
	void on_button_political_theme_clicked(QString theme = "POLITIQUE");
	void on_button_boring_theme_clicked(QString theme = "LOURD");
	void on_button_teacher_theme_clicked(QString theme = "PROF");
	void on_button_all_theme_clicked(QString theme = "TOUS");
};
#endif // MAINWINDOW_H
