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

///**
// * @brief Collect cards from another CardSet into this Deck
// *
// * @param cardSet The CardSet that collect cards
// */
//template <typename R, typename S>
//void Deck<R, S>::collect(CardSet<R, S> &cardSet)
//{
//    try
//    {
//        while (!cardSet.is_empty())
//        {
//            cardSet >> *this;
//        }
//    }
//    catch (const std::runtime_error& e)
//    {
//        std::cerr << "Caught exception: " << e.what() << std::endl;
//    }
//}