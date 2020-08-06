#pragma once
#include <iostream>
#include <fstream>

class Card
{
	char suit;
	char rank;
	int value;
	char suitUTF8[3];

public:
	Card(int _color = 0, int _value = 0);
	void setSuit(int _suit);
	void setValue(int _value);
	char getSuit() const { return suit; }
	char getRank() const {return rank;}
	int getValue() const { return value; }
	void display() const { std::cout << rank << suit<<" "; } 
	char* getSuitUTF8();
	void printCardToFile(std::ofstream& _file);

};
