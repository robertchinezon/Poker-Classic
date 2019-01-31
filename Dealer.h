#ifndef DEALER_H_
#define DEALER_H_
#include <iostream>
#include "DeckOfCards.h"

using namespace std;

class Dealer{
public:
	static int const SIZE_OF_HAND = 5;
	void display();
	static void dealHand(Card a[], DeckOfCards& d);
	static void convertToNumber(Card a[], int compareHand[]);
	static int* Difference(int compareHand[]);
	static bool isFlush(Card a[]);
	static void checkFlushSituation(int difference[], int compareHand[]);
	static void checkNormalSituation(int dif[], int compareHand[]);
	static int whoWon(int compareHand1[], int compareHand2[]);
	static int whoWonReturnX(int compareHand1[], int compareHand2[]);
	static string convertBackToString(int cH[], int x);
	static void reasonForWin(int compareHand[], int x);
};

#endif /* DEALER_H_ */
