#include <iostream>
#include "PinochleDeck.h"
#include "HoldEmDeck.h"

const int SUCCESS = 0;

int main(){
    // define two types of decks
    PinochleDeck pino_deck;
    HoldEmDeck hold_deck;

    // declare stack variables
    std::cout << "Pinochle Deck:" << std::endl;
    pino_deck.print(std::cout);
    std::cout << std::endl;

    std::cout << "Texas Hold'em Deck:" << std::endl;
    hold_deck.print(std::cout);
    std::cout << std::endl;

    // indicate successful completion
    return SUCCESS;
}