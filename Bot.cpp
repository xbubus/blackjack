#include "Bot.h"
#include "Casino.h"
Bot::Bot(Casino* _casino)
{
	braveryLevel = 0;
	casino = _casino;
	score = 0; 
	cardsCounter = 0;
	folded = false;
	*playerCards = nullptr;
}

void Bot::foldOrNot()
{
	if (folded == true) return;
	switch (braveryLevel)
	{
	case 1:
		if (score < 19)
		{
			folded = false;
			takeCard(casino->giveCard());
		}
		else folded = true;
		break;
	case 2:
		if (score < 17)
		{
			folded = false;
			takeCard(casino->giveCard());
		}
		else folded = true;
		break;
	case 3:
		if (score < 14)
		{
			folded = false;
			takeCard(casino->giveCard());
		}
		else folded = true;
		break;

	}
}
void Bot::setBraveryLevel(int _level)
{
	braveryLevel = _level;
}
