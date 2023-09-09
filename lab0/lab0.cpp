#include <iostream>
#include "PinochleDeck.h"
#include "HoldEmDeck.h"

const int SUCCESS=0;

int main(){
    PinochleDeck pino_deck;
    HoldEmDeck hold_deck;

    pino_deck.print(std::cout);
    hold_deck.print(std::cout);

    return SUCCESS;
}