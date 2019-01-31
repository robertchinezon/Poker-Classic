#include <iostream>
#include <sstream>
#include "Dealer.h"
#include <vector>
#include <algorithm>

using namespace std;

void Dealer::display(){
	DeckOfCards Deck;
	Deck.shuffle();
	Card temp;
	for (int x = 0; x < 52; x ++){
		temp = Deck.dealCard();
		cout << temp.toString() << endl;
	}
}

void Dealer::dealHand(Card a[], DeckOfCards& d){
	for (int x = 0; x < SIZE_OF_HAND; x++){
		a[x] = d.dealCard();
		//cout << a[x].toString() << endl;
	}
}

void Dealer::convertToNumber(Card a[], int compareHand[]){ //Used to assign numbers to all the card values, so the Difference function can compare the cards
 //Method makes numeric value of hand be decreasing order
	vector<int> numbHand;
	for (int x = 0; x < SIZE_OF_HAND; x ++){
		if (a[x].getFace() == 12){
			numbHand.push_back(-14);
		}
		else if (a[x].getFace() == 11){
			numbHand.push_back(-13);
		}
		else if (a[x].getFace() == 10){
			numbHand.push_back(-12);
		}
		else if (a[x].getFace() == 9){
			numbHand.push_back(-11);
		}
		else if (a[x].getFace() == 8){
			numbHand.push_back(-10);
		}
		else if (a[x].getFace() == 7){
			numbHand.push_back(-9);
		}
		else if (a[x].getFace() == 6){
			numbHand.push_back(-8);
		}
		else if (a[x].getFace() == 5){
			numbHand.push_back(-7);
		}
		else if (a[x].getFace() == 4){
			numbHand.push_back(-6);
		}
		else if (a[x].getFace() == 3){
			numbHand.push_back(-5);
		}
		else if (a[x].getFace() == 2){
			numbHand.push_back(-4);
		}
		else if (a[x].getFace() == 1){
			numbHand.push_back(-3);
		}
		else{
			numbHand[x] = -2;
		}
	}
	sort(numbHand.begin(), numbHand.end());
	for(int x = 0; x < numbHand.size(); x ++){
		numbHand[x] = numbHand[x]*-1;
	}
	for(int x = 0; x < numbHand.size() ; x ++){
		compareHand[x+1] = numbHand[x];
	}
}
	
int* Dealer::Difference(int compareHand[]){ //Used in determining what type of hand is being held, a dynamic array is created so the array can be returned by the function for the rest of the dealer functions to utilise, this information was found on your website with creating objects dynamically and 1 & 2d arrays

/*This methods calculates the difference between consecutive cards.
	 * Return 0 = match
	 * Return 1 = Different by 1, consecutive
	 * Return 2 = Non-consecutive 
*/

	int * difference = new int[4];
	int y = 1;
	int x = 0;
	do{
		if(compareHand[y]-compareHand[y+1] == 0){
			difference[x]=0;
		}
		else if(compareHand[y]-compareHand[y+1] == 1){
			difference[x]=1;
		}
		else{
			difference[x]=2;
		}
		x ++;
		y ++;
	} while(y < 5);
	if (compareHand[1]-compareHand[2] == 9 & difference[1] == 1 & difference[2] == 1 & difference[3] == 1){
		difference[0] = 1;
	}
	return difference;
}


bool Dealer::isFlush(Card a[]){ //Check to see if a flush is in play by comparing the suit indexs from the Card properties
	for (int x = 0; x< SIZE_OF_HAND - 1; x++){
		if (a[x].getSuit() != a[x+1].getSuit()){
			return false;
		}
		
	}
	return true;
}

void Dealer::checkFlushSituation(int difference[], int compareHand[]){ //Using numerical differences of Card face values to determine type of flush
	int counter = 0;
	for (int x = 0; x < 4; x ++){
		if (difference[x] == 1){
			counter ++;
		}
	}
	//Royal Flush
	if (counter == 4 & compareHand[5] == 10){
		compareHand[0] = 10;
	}
	//Straight Flush
	else if(counter == 4){
		compareHand[0] = 9;
	}
	//Flush
	else{
		compareHand[0] = 6;
	}
}

void Dealer::checkNormalSituation(int dif[], int compareHand[]){ 

/*This method assigns the poker hand rank to the first element of the array 
	 *compareHand. The next elements are rearranged so that the rank significant cards are
	 *placed at the front of the array and the high cards are placed in descending order
	 *at the back of the array.
*/
	int temp;
	//4 of a kind
	if (dif[0] == 0 & dif[1] == 0 & dif[2] == 0 & dif[3] != 0){
		compareHand[0]=8;
	}
	else if(dif[0] != 0 & dif[1] == 0 & dif[2] == 0 & dif[3] == 0){
		compareHand[0]=8;
		temp = compareHand[1];
		compareHand[1] = compareHand[5];
		compareHand[5] = temp;
	}
	//Full house
	else if(dif[0] == 0 & dif[1] == 0 & dif[2] != 0 & dif[3] == 0){
		compareHand[0]=7;
	}
	else if(dif[0] == 0 & dif[1] != 0 & dif[2] == 0 & dif[3] == 0){
		compareHand[0]=7;
		temp = compareHand[1];
		compareHand[1] = compareHand[5];
		compareHand[5] = temp;
		temp = compareHand[2];
		compareHand[2] = compareHand[4];
		compareHand[4] = temp;
	}
	//Straight
	else if(dif[0] == 1 & dif[1] == 1 & dif[2] == 1 & dif[3] == 1){
		compareHand[0]=5;
	}
	//3 of a kind
	else if(dif[0] == 0 & dif[1] == 0 & dif[2] != 0 & dif[3] != 0){
		compareHand[0]=4;
	}
	else if(dif[0] != 0 & dif[1] == 0 & dif[2] == 0 & dif[3] != 0){
		compareHand[0]=4;
		temp = compareHand[1];
		compareHand[1] = compareHand[4];
		compareHand[4] = temp;
		
	}
	else if(dif[0] != 0 & dif[1] != 0 & dif[2] == 0 & dif[3] == 0){
		compareHand[0]=4;
		temp = compareHand[1];
		compareHand[1] = compareHand[4];
		compareHand[4] = temp;
		temp = compareHand[2];
		compareHand[2] = compareHand[5];
		compareHand[5] = temp;
	}
	//2 pair
	else if(dif[0] == 0 & dif[1] != 0 & dif[2] == 0 & dif[3] != 0){
		compareHand[0]=3;
		
	}
	else if(dif[0] == 0 & dif[1] != 0 & dif[2] != 0 & dif[3] == 0){
		compareHand[0]=3;
		temp = compareHand[3];
		compareHand[3] = compareHand[5];
		compareHand[5] = temp;
	}
	else if(dif[0] != 0 & dif[1] == 0 & dif[2] != 0 & dif[3] == 0){
		compareHand[0]=3;
		temp = compareHand[1];
		compareHand[1] = compareHand[3];
		compareHand[3] = temp;
		temp = compareHand[3];
		compareHand[3] = compareHand[5];
		compareHand[5] = temp;
	}
	//Pair
	else if(dif[0] == 0 & dif[1] != 0 & dif[2] != 0 & dif[3] != 0){
		compareHand[0]=2;
	}
	else if(dif[0] != 0 & dif[1] == 0 & dif[2] != 0 & dif[3] != 0){
		compareHand[0]=2;
		temp = compareHand[1];
		compareHand[1] = compareHand[3];
		compareHand[3] = temp;
	}
	else if(dif[0] != 0 & dif[1] != 0 & dif[2] == 0 & dif[3] != 0){
		compareHand[0]=2;
		temp = compareHand[1];
		compareHand[1] = compareHand[3];
		compareHand[3] = temp;
		temp = compareHand[2];
		compareHand[2] = compareHand[4];
		compareHand[4] = temp;
	}
	else if(dif[0] != 0 & dif[1] != 0 & dif[2] != 0 & dif[3] == 0){
		compareHand[0]=2;
		temp = compareHand[1];
		compareHand[1] = compareHand[4];
		compareHand[4] = temp;
		temp = compareHand[2];
		compareHand[2] = compareHand[5];
		compareHand[5] = temp;
		temp = compareHand[3];
		compareHand[3] = compareHand[4];
		compareHand[4] = temp;
		temp = compareHand[4];
		compareHand[4] = compareHand[5];
		compareHand[5] = temp;
	}
	//High Card
	else{
		compareHand[0]=1;
	}

}

int Dealer::whoWon(int compareHand1[], int compareHand2[]){ //Checks each element of comparHands and determines a winner based on the first largest value between the two
	for (int x = 0; x < 6; x++){
		if (compareHand1[x] > compareHand2[x]){
			return 1;
		}
		else if (compareHand1[x] < compareHand2[x]){
			return 2;
		}
	}
	return 0;
}

int Dealer::whoWonReturnX(int compareHand1[], int compareHand2[]){
	for (int x = 0; x < 6; x++){
		if (compareHand1[x] > compareHand2[x]){
			return x;
		}
		else if (compareHand1[x] < compareHand2[x]){
			return x;
		}
	}
	return 0;
}

string Dealer::convertBackToString(int cH[], int x){
	string cardName;
	if (cH[x+1] == 2){
		return cardName = "Deuce";
	}
	else if (cH[x+1] == 3){
		return cardName = "Three";
	}
	else if (cH[x+1] == 4){
		return cardName = "Four";
	}
	else if (cH[x+1] == 5){
		return cardName = "Five";
	}
	else if (cH[x+1] == 6){
		return cardName = "Six";
	}
	else if (cH[x+1] == 7){
		return cardName = "Seven";
	}
	else if (cH[x+1] == 8){
		return cardName = "Eight";
	}
	else if (cH[x+1] == 9){
		return cardName = "Nine";
	}
	else if (cH[x+1] == 10){
		return cardName = "Ten";
	}
	else if (cH[x+1] == 11){
		return cardName = "Jack";
	}
	else if (cH[x+1] == 12){
		return cardName = "Queen";
	}
	else if (cH[x+1] == 13){
		return cardName = "King";
	}
	else{
		return cardName = "Ace";
	}
}

void Dealer::reasonForWin(int compareHand[], int x){
	if (x == 0){
		if (compareHand[x] == 1){
			cout <<"won with a high card of " + Dealer::convertBackToString(compareHand, x) << endl;
		}
		else if(compareHand[x] == 2){
			cout <<"won with a pair of " + Dealer::convertBackToString(compareHand, x) + "s" << endl;
		}
		else if(compareHand[x] == 3){
			cout <<"won with a high two pair of " + Dealer::convertBackToString(compareHand, x) + "s" << endl;
		}
		else if(compareHand[x] == 4){
			cout <<"won with three of " + Dealer::convertBackToString(compareHand, x) << endl;
		}
		else if(compareHand[x] == 5){
			cout <<"won with a straight" << endl;
		}
		else if(compareHand[x] == 6){
			cout <<"won with a flush" << endl;
		}
		else if(compareHand[x] == 7){
			cout <<"won with a full house" << endl;
		}
		else if(compareHand[x] == 8){
			cout <<"won with four of " + Dealer::convertBackToString(compareHand, x) << endl;
		}
		else if(compareHand[x] == 9){
			cout <<"won with a straight flush" << endl;
		}
		else{
			cout <<"won with a royal flush" << endl;
		}
	}
	else{
		if (compareHand[0] == 1){
			cout <<"won with a high card of " + Dealer::convertBackToString(compareHand, (x-1)) << endl;
		}
		else if(compareHand[0] == 2){
			if (x > 2){
				cout <<"won with a high card of " + Dealer::convertBackToString(compareHand, (x-1)) << endl;
			}
			cout <<"won with a pair of " + Dealer::convertBackToString(compareHand, (x-1)) + "s" << endl;
		}
		else if(compareHand[0] == 3){
			if (x > 4){
				cout <<"won with a high card of " + Dealer::convertBackToString(compareHand, (x-1)) << endl;
			}
			cout <<"won with a high two pair of " + Dealer::convertBackToString(compareHand, (x-1)) + "s" << endl;
		}
		else if(compareHand[0] == 4){
			if (x > 3){
				cout <<"won with a high card of " + Dealer::convertBackToString(compareHand, (x-1)) << endl;
			}
			cout <<"won with three of " + Dealer::convertBackToString(compareHand, (x-1)) << endl;
		}
		else if(compareHand[0] == 5){
			cout <<"won with a straight of high card " + Dealer::convertBackToString(compareHand, (x-1)) << endl;
		}
		else if(compareHand[0] == 6){
			cout <<"won with a flush of high card " + Dealer::convertBackToString(compareHand, (x-1)) << endl;
		}
		else if(compareHand[0] == 7){
			cout <<"won with a full house of high card " + Dealer::convertBackToString(compareHand, (x-1)) << endl;
		}
		else if(compareHand[0] == 8){
			cout <<"won with four of high card " + Dealer::convertBackToString(compareHand, (x-1)) << endl;
		}
		else if(compareHand[0] == 9){
			cout <<"won with a straight flush" << endl;
		}
	}
}








