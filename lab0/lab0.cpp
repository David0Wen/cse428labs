#include <iostream>
#include "PinochleDeck.h"
#include "HoldEmDeck.h"

const int SUCCESS=0;

int main(){
    PinochleDeck pino_deck;
    HoldEmDeck hold_deck;

    std::cout << "Pinochle Deck:" << std::endl;
    pino_deck.print(std::cout);
    std::cout << std::endl;

    std::cout << "Texas Hold'em Deck:" << std::endl;
    hold_deck.print(std::cout);
    std::cout << std::endl;

    return SUCCESS;
}