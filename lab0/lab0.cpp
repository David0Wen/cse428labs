/*
// File: lab0.cpp
// Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
// Purpose: contain the main function, test whether the deck is correctly initialized.
*/
#include <iostream>
#include "PinochleDeck.h"
#include "HoldEmDeck.h"

const int SUCCESS = 0;

int main(){
	// define two types of decks
	PinochleDeck pino_deck;
	HoldEmDeck hold_deck;

	// print the deck
	std::cout << "Pinochle Deck:" << std::endl;
	pino_deck.print(std::cout);
	std::cout << std::endl;

	std::cout << "Texas Hold'em Deck:" << std::endl;
	hold_deck.print(std::cout);
	std::cout << std::endl;

	// indicate successful completion
	return SUCCESS;
}