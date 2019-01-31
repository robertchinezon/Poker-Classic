#include <iostream>
#include <sstream>
#include "DeckOfCards.h"

using namespace std;

DeckOfCards::DeckOfCards(){
	nextCard = 0;
	deck = new Card[SIZE_OF_DECK]; //A dynamic array is created here as outlined on the assignment and the techniques used in impelenting it was learned on your website
	int z = 0;
	int x = 0;
	while (x < SIZE_OF_DECK) {
		for (int y = 0; y < SIZE_OF_SUIT; y ++){
			deck[x] = Card(z, y);
			//cout << deck[x].toString() << endl;
			x++;
		}
			z ++;

	}
}

void DeckOfCards::shuffle(){
		srand(time(0));
		Card temp;
		int rndnumb;
		for (int x = 0; x < SIZE_OF_DECK; x ++){
			rndnumb = rand() % SIZE_OF_DECK;
			temp = deck[rndnumb];
			deck[rndnumb] = deck[x];
			deck[x] = temp;
		}
}

Card DeckOfCards::dealCard(){
	int temp = nextCard;
	nextCard ++;
	return deck[temp];
}

bool DeckOfCards::moreCards(){
	if (nextCard < SIZE_OF_DECK){
		return true;
	}
	else{
		return false;
	}
}

void DeckOfCards::printDeck(){
	for (int x = 0; x < SIZE_OF_DECK; x++){
		cout << deck[x].toString() << endl;
	}
}

DeckOfCards::~DeckOfCards(){
	//cout << "Deck Gone" << endl;
	delete[] deck; //pointer is deleted
}







