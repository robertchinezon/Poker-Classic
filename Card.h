#ifndef CARD_H_
#define CARD_H_
#include <iostream>

using namespace std;

class Card{
int face, suit;

public:
	Card& operator=(const Card& otherCard); //Overloaded assignment operator to create deep copy of Card Objects rather than a shallow copy
	static string faces[];
	static string suits[];
	int getFace();
	int getSuit();
	Card();
	Card(int f, int s);
	string toString();
	~Card();
};



#endif /* CARD_H_ */



