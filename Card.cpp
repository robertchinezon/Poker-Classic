#include <iostream>
#include <sstream>
#include "Card.h"

using namespace std;

string Card::faces[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
string Card::suits[] = {"Hearts", "Diamonds", "Spades", "Clubs"};

Card::Card(){
	face = 0;
	suit = 0;
}

Card::Card(int face, int suit){
	this->face = face;
	this->suit = suit;
}

string Card::toString(){
  stringstream ss;
  ss << faces[face];
  ss << " of ";
  ss << suits[suit]; 
  return ss.str();
}

int Card::getFace(){
	return face;
}

int Card::getSuit(){
	return suit;
}

Card& Card::operator =(const Card& otherCard){
	if (this != &otherCard){
		this->face = otherCard.face;
		this->suit = otherCard.suit;
	}
	return *this;
}

Card::~Card(){
}
