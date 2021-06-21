#include <string>

#include <QObject>

#pragma once
class Round : public QObject
{
	Q_OBJECT
private:
	bool hasPlayerSmiled;
	std::string joke;
};

