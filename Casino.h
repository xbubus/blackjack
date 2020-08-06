#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Card.h"
#include <fstream>
#include <iomanip>
#include "time.h" //sprawdzic czy w mainie nie wystarczy ten include
#include "windows.h"
#include "Bot.h"

#define MAX_PLAYERS_IN_CASINO 6
class Player;


const int linesInBaner = 8;
class Casino
{
	
	Card deck[52];
	int cardCounter;
	Player* players[MAX_PLAYERS_IN_CASINO];
	int playersCounter;
	int winnersCounter;
	bool allPlayersFolded;
	char bannerData[linesInBaner][1024];
	bool isBannerLoaded; // ? inna nazwa
	int numberOfBots;
	int numberOfHumanPlayers;
	


public://uporzadkowac
	
	Casino();
	~Casino();
	void displayDeck();
	void shuffle();
	Card* giveCard();
	void createHumanPlayer();
	void createBotPlayer();
	void findWinners();
	bool hasAllPlayersFolded();
	void resetGame();
	void manageGame();
	void displayAllPlayersData();
	void loadBanner();
	void displayBanner();
	int askPlayerForBotBraveryLevel();
	void saveResultsToFile();
	void setupNicknamesAndBravery();
	void setNumberOfHumanPlayers(int _numberOfHumanPlayers);
	void setNumberOfBotPlayers(int _numberOfBotsPlayers);
	void deleteAllPlayers();
	void createPlayers();
};