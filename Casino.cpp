#include "Casino.h"
#include "Player.h"
#include "conio.h"
#include <iostream>

Casino::Casino()
{
	
	isBannerLoaded = false;
	allPlayersFolded = false;
	playersCounter = 0;
	cardCounter = 0;
	winnersCounter = 0;
	for (int i = 0; i < 52; i++)
	{
		deck[i].setSuit(i/13);
		deck[i].setValue(i % 13);
	}

	loadBanner();
}

Casino::~Casino()
{
	deleteAllPlayers();
}
void Casino::displayDeck()
{
	for (int i = 0; i < 52; i++)
	{
		deck[i].display();
	}
}
void Casino::shuffle()
{
	for (int i = 0; i < 100; i++)
	{
		int index1 = rand() % 52;
		Card temp = deck[index1];
		int index2 = rand() % 52; 
		deck[index1] = deck[index2];
		deck[index2] = temp;


	}
}

Card* Casino::giveCard()
{
	if (cardCounter < 52)
	{
		return &deck[cardCounter++];
	}
	std::cout << "There are no cards in deck!";

}

void Casino::createHumanPlayer()
{
	players[playersCounter] = new Player(this);
	playersCounter++;
}
void Casino::createBotPlayer()
{
	players[playersCounter] = new Bot(this);
	playersCounter++;
}
void Casino::findWinners() 
{
	winnersCounter = 0;
	int currentWinningScore = -1;
	for (int i = 0; i < numberOfHumanPlayers + numberOfBots; i++)
	{
		if (players[i]->getScore() <= 21 && players[i]->getScore() >= currentWinningScore)
		{
			if (players[i]->getScore() == currentWinningScore) winnersCounter++;
			else winnersCounter = 1;
			players[i]->setWon(true);
			currentWinningScore = players[i]->getScore();
			
		}
	}
	for (int i = 0; i < numberOfHumanPlayers + numberOfBots; i++)
	{
		if (players[i]->getScore() < currentWinningScore)
			players[i]->setWon(false);
	}
	
}





bool Casino::hasAllPlayersFolded()
{
	for (int i = 0; i < numberOfHumanPlayers + numberOfBots; i++)
	{
		if (players[i]->getFolded() == false) return false;
	}
	return true;
}
void Casino::resetGame()
{

	shuffle();
	for (int i = 0; i < numberOfHumanPlayers+numberOfBots; i++)
	{
		players[i]->resetStats();
	}
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < numberOfHumanPlayers+numberOfBots; i++)
		{
			players[i]->takeCard(this->giveCard());
		}
	}
}
void Casino::manageGame()
{
	resetGame();
	while (!hasAllPlayersFolded())
	{
		for (int i=0;i<numberOfHumanPlayers+numberOfBots;i++)
		{
			if (players[i]->getFolded()==false)
			{
				displayBanner();
				std::cout << "Hi player " << players[i]->getName() << std::endl;
				std::cout << "Its your turn, your cards and score:\n";
				players[i]->displayPlayerCardsAndScore();
				players[i]->foldOrNot();
				system("cls");
			}
		}
	}
	displayBanner();
	std::cout << "Final results:\n";
	displayAllPlayersData();
	findWinners();
	switch (winnersCounter)
	{
	case 0:
		std::cout << "\nEveryone lost\n";
		return;
		break;
	case 1:
		std::cout << "\nThe winner is:\n";
		break;
	default:
		std::cout << "\nThe winners are:\n";
		break;
	}
	for (int i = 0; i < numberOfHumanPlayers + numberOfBots; i++)
	{
		if (players[i]->getWon() == true)
		{
			std::cout << players[i]->getName() << std::endl;
		}
	}	
	saveResultsToFile();
	system("pause");
}

void Casino::displayAllPlayersData()
{
	std::cout << std::left << std::setw(21) << "Name:" << "Cards:" << std::right << std::setw(29) << "Score:\n";
	for (int i = 0; i < numberOfHumanPlayers+numberOfBots; i++)
	{

		std::cout<<std::left<<std::setw(21) << players[i]->getName();
		players[i]->displayPlayerCards();

		std::cout <<std::right<<  std::setw(30 - 3*(players[i]->getCardsCounter())) << players[i]->getScore() << std::endl;
	}
}

void Casino::loadBanner()
{
	char line[256];
	std::ifstream file;
	file.open("banner.txt", std::ifstream::in);
	if (file.is_open())
	{
		int i = 0;
		while (file.getline(line, 1024))
		{
			if (i >= linesInBaner) break;
			strcpy_s(bannerData[i], line);
			i++;
		}
		file.close();
		isBannerLoaded = true;
	}
}

void Casino::displayBanner()
{
	if (!isBannerLoaded)return;
	std::cout << std::endl;
	for (int i = 0; i < linesInBaner; i++)
	{
		std::cout.width(70);
		std::cout << bannerData[i] << std::endl;
	}
	std::cout << std::endl;
}

int Casino::askPlayerForBotBraveryLevel()
{
	int bravery = -1;;
	std::cout << "1 - risking \n";
	std::cout << "2 - normal \n";
	std::cout << "3 - cautious \n";
	while (1) {
		std::cin >> bravery;
		if (std::cin.fail() == true || bravery < 1 || bravery>3)
		{
			std::cout << "Something went wrong. Try again." << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}
		else return bravery;
	}
}

void Casino::saveResultsToFile()
{
	const time_t time = std::time(nullptr);
	std::ofstream file;
	file.open("results.txt", std::ofstream::app);
	if (file.is_open())
	{
		file<< std::put_time(std::localtime(&time), "%F_%T");
		file << '\n';
		file << std::left << std::setw(21) << "Name:" << "Cards:" << std::right << std::setw(29) << "Score:\n";

		for (int i = 0; i < numberOfHumanPlayers + numberOfBots; i++)
		{

			file << std::left << std::setw(21) << players[i]->getName();
			for (int j = 0; j < players[i]->getCardsCounter(); j++)
			{
				players[i]->getPlayerCards()[j]->printCardToFile(file);

			}
			file << std::right << std::setw(30 - 2 * (players[i]->getCardsCounter())) << players[i]->getScore() << std::endl;
		}
		switch (winnersCounter)
		{
		case 0:
			file << "Everyone lost\n";
			return;
			break;
		case 1:
			file << "The winner is:\n";
			break;
		default:
			file << "The winners are:\n";
			break;
		}
		for (int i = 0; i < numberOfHumanPlayers + numberOfBots; i++)
		{
			if (players[i]->getWon() == true)
			{
				file << players[i]->getName() << std::endl;
			}
		}
		std::cout << "Results has been saved to file\n";
		file << "\n\n";
		file.close();
	}
}

void Casino::setupNicknamesAndBravery()
{
	char nickname[MAX_NAME_SIZE];
	system("cls");
	std::cout << "Starting new game:\n";
	for (int i = 0; i < numberOfHumanPlayers; i++)
	{

		std::cout << "Hi player " << i + 1 << "\nWrite your nickname: \n";
		std::cin >> nickname;
		std::cout << nickname;
		players[i]->setName(nickname);
		system("cls");
	}
	
	for (int i = numberOfHumanPlayers; i < numberOfBots + numberOfHumanPlayers; i++)
	{
		sprintf_s(nickname, "Bot%d", i - numberOfHumanPlayers + 1);
		players[i]->setName(nickname);
		std::cout << "Choose bravery level for "<<players[i]->getName()<<"\n";
		players[i]->setBraveryLevel(this->askPlayerForBotBraveryLevel());
	}
	system("cls");
}

void Casino::setNumberOfBotPlayers(int _numberOfBotsPlayers)
{
	
	numberOfBots = _numberOfBotsPlayers;
}

void Casino::setNumberOfHumanPlayers(int _numberOfHumanPlayers)
{
	numberOfHumanPlayers = _numberOfHumanPlayers;
	
}
void Casino::deleteAllPlayers()
{
	for (int i = 0; i < numberOfHumanPlayers + numberOfBots; i++) 
	{
		delete players[i];
	}
}

void Casino::createPlayers()
{
	playersCounter = 0;
	cardCounter = 0;
	for (int i = 0; i < numberOfHumanPlayers; i++)
	{
		createHumanPlayer();
	}
	for (int i = 0; i < numberOfBots; i++)
	{
		createBotPlayer();
	}
}