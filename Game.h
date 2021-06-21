#include <string>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <QFrame>
#include <QtWidgets>
#include <QObject>

#pragma once
class Game : public QFrame
{
	Q_OBJECT


private:
	bool didUserWin;
	bool isMultiplayerMode;
	std::string questionsList[10];
	std::string chosenTheme;
	int currentRoundIndex;
	bool hasPlayerSmiled;

public:

	signals:
		void closeGame();
		void changeTheme(std::string theme);
		void changeMultiplayerMode(bool value);

	public slots:
		void setMultiplayerMode(bool chosenMode);
		void setChosenTheme(std::string theme);
};

