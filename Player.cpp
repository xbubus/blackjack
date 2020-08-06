#include "Player.h"
#include "Casino.h"


Player::Player(Casino * _casino)
{
	casino = _casino;
	score = 0;
	cardsCounter = 0;
	*playerCards = nullptr;
	folded = false;
	won = false;
	strcpy_s(name, "");
	
}

void Player::takeCard(Card* _card)
{
	if (cardsCounter < 10)
	{
		playerCards[cardsCounter++] = _card;
		score += _card->getValue();
		if (score >= 21) folded = true;
		return;
	}
	std::cout<<"Player cannot have more than 10 cards\n";
}

void Player::displayPlayerCards()
{
	for (int i = 0; i < cardsCounter; i++)
	{
		playerCards[i]->display();
	}
}

void Player::displayPlayerCardsAndScore()
{
	for (int i = 0; i < cardsCounter; i++)
	{
		playerCards[i]->display();
	}
	std::cout <<"  "<< score << std::endl;


}

bool Player::getFolded()
{
	return folded;
}
void Player::setFolded(bool _folded)
{
	folded = _folded;
}

 void Player::foldOrNot() 
{
	if (folded == true) return;
	int choice;
	std::cout << "\nEnter 1 to fold or 0 to take card :" << std::endl;
	while (1) {
		std::cin >> choice;
		if (std::cin.fail() == true || choice < 0 || choice>1)
		{
			std::cout << "Something went wrong. Try again." << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}
		else
		{
			folded = choice;
			if (folded == false)
			{
				takeCard(casino->giveCard());
				std::cout << "Your new cards and score: \n";
				this->displayPlayerCardsAndScore();
				std::cout << "\nYour move is over\n";
				system("pause"); // linux/mac-> system("read");
			}
			return;
		}
	}

	

}

int Player::getScore()
{
	return score;
}

char* Player::getName()
{
	return name;
}

void Player::resetStats()
{
	for (int i = 0; i < cardsCounter; i++)
	{
		playerCards[i] = nullptr;
	}
	folded = false;
	cardsCounter = 0;
	score = 0;
	won = false;
	
}
int Player::getCardsCounter()
{
	return cardsCounter;
}

bool Player::getWon()
{
	return won;
}
void Player::setWon(bool _won)
{
	won = _won;
}
void Player::setName(char* _name)
{
	strcpy_s(name, _name);
}
void Player::setBraveryLevel(int _level)
{
	std::cout<<"You are not a BOT!\n";
}

Card** Player::getPlayerCards()
{
	return playerCards;
}