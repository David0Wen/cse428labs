/**
 * File: CardSet_T.cpp
 * Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
 * Purpose: Implementation of template structure: cardset.
 */
#include "CardSet_T.h"
#include <iostream>


 /**
  * @brief Prints the CardSet to the given output stream
  *
  * @param os Output stream to print the CardSet to
  * @param linesize Number of cards to print per line
  */
template<typename R, typename S>
void CardSet<R, S>::print(std::ostream &os, size_t linesize)
{
    size_t index = 0;
    card_iter iter = myCardSet.begin();
    for (; iter != myCardSet.end(); ++iter)
    {
        ++index;
        os << (*iter) << " ";
        if (index % linesize == 0) {
            os << std::endl;
        }
    }
    os << std::endl;  // New add to fix bug, always add a newline at the end
}

/**
 * @brief Checks if the CardSet is empty
 *
 * @return True if empty
 */
template<typename R, typename S>
bool CardSet<R, S>::is_empty() {
    return myCardSet.empty();
}

/**
 * @brief Performs a shift operation between two CardSets
 *
 * @param other The CardSet object to which the card will be moved
 * @return Reference to the calling CardSet object
 * @throws std::runtime_error if the CardSet is empty
 */
template<typename R, typename S>
CardSet<R, S> &CardSet<R, S>::operator>>(CardSet<R, S> &other) {
    if (is_empty()) {
        throw std::runtime_error("CardSet is empty, cannot perform shift operation!");
    }

    other.myCardSet.push_back(myCardSet.back());
    myCardSet.pop_back();

    return *this;
}

/**
 * @brief Return an iterator to the start of myCardSet
 * @return The start of myCardSet
 */
template<typename R, typename S>
typename CardSet<R, S>::card_iter CardSet<R, S>::begin() {
    return myCardSet.begin();
}

/**
 * @brief Return an iterator to the end of myCardSet
 * @return The end of myCardSet
 */
template<typename R, typename S>
typename CardSet<R, S>::card_iter CardSet<R, S>::end() {
    return myCardSet.end();
}

/**
 * @brief Use std::sort for the CardSet
*/
template<typename R, typename S>
void CardSet<R, S>::sort() {
    std::sort(begin(), end(), lessRank<R, S>);
}

/**
 * @brief Add cards from another CardSet
 *
 * @param other another CardSet to add
 */
template<typename R, typename S>
void CardSet<R, S>::addCards(CardSet<R, S> &other) {
    myCardSet.insert(myCardSet.end(), other.begin(), other.end());
}

/**
 * @brief Move cards from another CardSet into this Deck
 *
 * @param other another CardSet
 */
template<typename R, typename S>
void CardSet<R, S>::collect(CardSet<R, S> &other) {
    std::move(other.begin(), other.end(), std::back_inserter(myCardSet));
    other.myCardSet.clear();
}

/**
 * @brief Collect cards that match certain criteria
 *
 * @param deck A CardSet to be collected and estimated
 * @param predicate to determine whether a Card should be collected
 */
template<typename R, typename S>
void CardSet<R, S>::collect_if(CardSet<R, S> &deck, std::function<bool(card_type&)> predicate) {
    std::vector<card_type> temp;
    std::copy_if(deck.begin(), deck.end(), std::back_inserter(temp), predicate);

    myCardSet.insert(myCardSet.end(), temp.begin(), temp.end());

    auto newEnd = std::remove_if(deck.begin(), deck.end(), predicate);
    deck.myCardSet.erase(newEnd, deck.end());
}

/**
 * @brief Request specific Card form another CardSet
 *
 * @param other The requested CardSet
 * @param rank the certain rank for the request
 * @return true if found and moved the card; false if not
 */
template<typename R, typename S>
bool CardSet<R, S>::request(CardSet<R, S> &other, const R &rank) {
    auto it = std::find_if(other.begin(), other.end(), [&rank](const card_type &card) {
        return card.myRank == rank;
    });

    if (it != other.end()) {
        myCardSet.push_back(std::move(*it));
        other.myCardSet.erase(it);
        return true;
    }

    return false;
}