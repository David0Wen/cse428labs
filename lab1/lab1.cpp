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

	try {
        if (!pino_deck.is_empty()) {

        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

	// print the deck
	std::cout << "Pinochle Deck:" << std::endl;
    pino_deck.shuffle();
    pino_deck.print(std::cout, 8);
    std::cout << std::endl;

	std::cout << "Texas Hold'em Deck:" << std::endl;
    hold_deck.shuffle();
    hold_deck.print(std::cout, 4);
    std::cout << std::endl;

	// indicate successful completion
	return SUCCESS;
}