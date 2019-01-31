#ifndef DeckOfCards_H_
#define DeckOfCards_H_
#include <iostream>
#include "Card.h"

using namespace std;

class DeckOfCards{
	int nextCard; //This is a more intuitive name for the currentCard variable
	int const SIZE_OF_FACE = 13;
	int const SIZE_OF_SUIT = 4;
	int const SIZE_OF_DECK = 52;
	Card * deck;
public:
	DeckOfCards();
	void shuffle();
	Card dealCard();
	bool moreCards();
	void printDeck(); //Function to display all the elements in the deck array
	~DeckOfCards();
};


#endif /* DeckOfCards_H_ */


