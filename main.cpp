#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "time.h"
#include "Casino.h"


std::ostream& operator<<(std::ostream& os, Card& card);
void chooseNumberFrom1To3(int& number);


int main()
{
	Casino c1;
	int choice = 0;
	bool gameON = true;
	int numberOfHumanPlayers = 0;
	int numberOfBotPlayers = 0;
	srand(time(NULL));
   while (gameON)
   {
	   std::cout << "Enter 1 to start new game with the same players\n";
	   std::cout << "Enter 2 to start new game with other players\n";
	   std::cout << "Enter 3 to exit program\n";
	   chooseNumberFrom1To3(choice);
	   switch (choice)
	   {
	   case 1:
		   system("cls");
		   if (numberOfHumanPlayers == 0)
		   {
			   std::cout << "\nYou have to start first game with option 2!\n\n";
				break;
		   }
		   system("cls");
		   c1.manageGame();
		   break;
	   case 2:
		   system("cls");
		   c1.deleteAllPlayers();
		   std::cout << "Choose how many human players will play(1-3):\n";
		   chooseNumberFrom1To3(numberOfHumanPlayers);
		   std::cout << "Choose how many bots will play(1-3):\n";
		   chooseNumberFrom1To3(numberOfBotPlayers);
		   c1.setNumberOfBotPlayers(numberOfBotPlayers);
		   c1.setNumberOfHumanPlayers(numberOfHumanPlayers);
		   c1.createPlayers();
		   c1.setupNicknamesAndBravery();
		   c1.manageGame();
		   break;
	   case 3:
		   gameON = false;
		   break;
	   }

   }


	


}
std::ostream& operator<<(std::ostream& os, Card& card)
{
	os << card.getRank() << card.getSuit() << " ";
	return os;
}
void chooseNumberFrom1To3(int& number)
{
	while (1) {
		std::cin >> number;
		if (std::cin.fail() == true || number < 1 || number>3)
		{
			std::cout << "Something went wrong. Try again." << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}
		else return;
	}
}