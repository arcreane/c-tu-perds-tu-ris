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
		"C'est l'histoire d'un papier qui tombe � l'eau. Il crie : Au secours ! J'ai pas pied !"
	};
	
	// Predefined config
	int playerCount;
	
	QString chosenTheme;
	Ui::MainWindow* ui;
	bool didUserWin;
	bool isMultiplayerMode;
	int currentCounter = 0;
	void showTheme();
	void showJoke();
	void changeJokeCounter();
	void showJokeIndex();
	void endGame();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool multiplayerMode() const { return this->isMultiplayerMode; }
	QString theme() const { return this->chosenTheme; }

	void startGame();

	void nextRound();

	void countDown();

	bool CloseGame = false;

	bool hasPlayerSmiled = false;

	int nextRoundIndex;

	void startTimer();

	void startRound();

	void setTitle(QString text);

	void setHasPlayerSmiled(bool playerSmiled);

	void setChosenTheme(QString theme);

	void setMultiplayerMode(bool multiplayer);

private slots:
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
    void on_back_to_menu_clicked();
	void on_button_exit_clicked();
	
};
#endif // MAINWINDOW_H
