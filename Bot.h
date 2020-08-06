#pragma once
#include "Player.h"
class Casino;
class Bot : public Player
{

	int braveryLevel; 
public:
	 Bot(Casino* _casino);
	 void foldOrNot();
	 void setBraveryLevel(int _level);
};