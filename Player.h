#pragma once
#include "Card.h"
#include <conio.h>
#define MAX_PLAYER_CARDS 10
#define MAX_NAME_SIZE 25
class Casino;

class Player
{
protected:
	Casino *casino; 
	int score;
	int cardsCounter;
	Card* playerCards[MAX_PLAYER_CARDS];
	bool folded;
	char name[MAX_NAME_SIZE];
	bool won;

public://uporzadkowac
	Player(Casino * _casino=nullptr);
	void takeCard(Card* _card);
	void displayPlayerCardsAndScore();
	void displayPlayerCards();
	bool getFolded();
	void setFolded(bool _folded);
	virtual void foldOrNot(); 
	int getScore();
	char* getName();
	void resetStats(); 
	int getCardsCounter();
	bool getWon();
	void setWon(bool _won);
	void setName(char *_name);
	virtual void setBraveryLevel(int _level); //tutaj chcia³em zastosowaæ metodê czysto wirtualn¹,ale wtedy klasa uznawana jest za abstrakcyjna i nie da sie stworzyc jej instancji
	Card** getPlayerCards();
};