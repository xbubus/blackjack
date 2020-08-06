#include "Card.h"

const char suits[] = { 3, 4, 5, 6 };
const char ranks[] = { '2', '3', '4', '5', '6', '7', '8', '9', 'D', 'J', 'Q', 'K', 'A' };
const int values[] = { 2,   3,   4,   5,   6,   7 ,  8,   9,  10,   2,   3,   4,  11 };
const char suitsUTF8[][3] = { { '\xe2','\x99','\xa5' },{ '\xe2','\x99','\xa6' },{ '\xe2','\x99','\xa3' },{ '\xe2','\x99','\xa0' } };

Card::Card(int _suit, int _value) {
	setSuit(_suit);
	setValue(_value);
}

void Card::setSuit(int _suit) {
	if (_suit < 4) {
		suit = suits[_suit];
		for (int i = 0; i < 3; i++) suitUTF8[i] = suitsUTF8[_suit][i];
	}
}
void Card::setValue(int _value) {
	if (_value < 13) {
		rank = ranks[_value];
		value = values[_value];
	}
}

char* Card::getSuitUTF8()
{
	return suitUTF8;
}
void Card::printCardToFile(std::ofstream& _file)
{
	_file << rank;
	for (int k = 0; k < 3; k++) _file << suitUTF8[k];
}