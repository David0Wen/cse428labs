/**
 * File: Deck_T.cpp
 * Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
 * Purpose: Implementation of template class: Deck.
 */
#include "Deck_T.h"


/**
 * @brief Shuffle the Deck of cards.
 */
template<typename R, typename S>
void Deck<R, S>::shuffle()
{
    std::random_device deviceGenerator;
    std::mt19937 numGenerator(deviceGenerator());
    std::shuffle(CardSet<R, S>::myCardSet.begin(), CardSet<R, S>::myCardSet.end(), numGenerator);
}