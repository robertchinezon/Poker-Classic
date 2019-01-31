#include <iostream>
#include <stdlib.h>
#include "Card.h"
#include "DeckOfCards.h"
#include "Dealer.h"


using namespace std;

int bet(int compMoney){
	int bet;
	if (compMoney == 0){
		return -1;
	}
	
}

int main() {
	//Dealer newDeck;
	DeckOfCards gameDeck;
	Card hand1[5];
	Card hand2[5];
	int compareHand1[6];
	int compareHand2[6];
	int input;
	int yourBet;
	int userMoney = 1000;
	int compMoney = 1000;
	int pool = 0;
	int rounds = 1;
	//newDeck.display();
	//gameDeck.printDeck();
	cout << "Welcome to Poker:" << endl;
	do{
		gameDeck.shuffle();
		cout << endl;
		cout << "Your hand: " << endl;
		Dealer::dealHand(hand1, gameDeck);
		Dealer::dealHand(hand2, gameDeck);
		for (int x = 0; x < 5; x ++){
			cout << hand1[x].toString() << endl;
		}
		cout << endl;
		cout << "Your moneys: " << userMoney << endl;
		
		cout << "Your Actions: \n 1: Bet any positive integer amount \n 2: Bet 0 to call \n 3: Bet -1 to fold \n 4: Bet -100 to exit the game" << endl;
		cin >> yourBet;
		pool = 2 * (pool + yourBet);
		userMoney = userMoney - yourBet;
		compMoney = compMoney - yourBet;
		Dealer::convertToNumber(hand1, compareHand1);
		Dealer::convertToNumber(hand2, compareHand2);
		
		if (yourBet >= 0){
			if(Dealer::isFlush(hand1) == true){
				Dealer::checkFlushSituation(Dealer::Difference(compareHand1), compareHand1);
				cout << endl;
			}
			else{
				Dealer::checkNormalSituation(Dealer::Difference(compareHand1), compareHand1);
				cout << endl;
			}
			
			if(Dealer::isFlush(hand2) == true){
				Dealer::checkFlushSituation(Dealer::Difference(compareHand2), compareHand2);
				cout << endl;
			}
			else{
				Dealer::checkNormalSituation(Dealer::Difference(compareHand2), compareHand2);
				cout << endl;
			}
			
			if (Dealer::whoWon(compareHand1, compareHand2) == 1){
				cout << "Player" << endl;
				Dealer::reasonForWin(compareHand1, Dealer::whoWonReturnX(compareHand1, compareHand2));
				userMoney = userMoney + pool;
			}
			else if(Dealer::whoWon(compareHand1, compareHand2) == 2){
				cout << "Computer" << endl;
				Dealer::reasonForWin(compareHand2, Dealer::whoWonReturnX(compareHand1, compareHand2));
				compMoney = compMoney + pool;
			}
			else{
				cout << "Its a tie!" << endl;
				userMoney += (pool/2);
				compMoney += (pool/2);
			}
		}
		else if (yourBet == -100){
			exit(EXIT_FAILURE);
		}
		else{
			cout << "Computer Wins from Fold" << endl;
		}
		
		cout << endl;
		cout << "Opponent's hand: " << endl;
		for (int x = 0; x < 5; x ++){
			cout << hand2[x].toString() << endl;
		}
		cout << endl;
		cout << "Comp's moneys: " << compMoney << endl;
		pool = 0;
		cout << "End of round: " << rounds;
		cout << endl;
		rounds ++;
	} while(yourBet != -100);
	
	
	return 0;
}
