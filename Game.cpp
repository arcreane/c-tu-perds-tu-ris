#include "Round.h"
#include "Game.h"
#include <chrono>
#include <string>
#include <opencv2/highgui.hpp>



//void Game::endGame() {
//	emit closeGame();
//};

void Game::setMultiplayerMode(bool value)
{
    emit changeMultiplayerMode(value);
}

void Game::setChosenTheme(std::string value)
{
    qInfo() << "Hi";
    if (value != this->chosenTheme) {
        this->chosenTheme = value;
        emit changeTheme(value);

    }
}