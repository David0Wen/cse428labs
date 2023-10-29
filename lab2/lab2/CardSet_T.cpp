/**
// File: CardSet_T.cpp
// Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
// Purpose: Implementation of template structure: cardset.
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
void CardSet<R, S>::print(std::ostream& os, size_t linesize)
{
	size_t index = 0;
	typename std::vector< Card<R, S> >::iterator iter = myCardSet.begin();
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
CardSet<R, S>& CardSet<R, S>::operator>>(CardSet<R, S>& other) {
	if (is_empty()) {
		throw std::runtime_error("CardSet is empty, cannot perform shift operation!");
	}

	other.myCardSet.push_back(myCardSet.back());
	myCardSet.pop_back();

	return *this;
}

/**
 * @brief Controlled violation of encapsulation: get the pointer to the protected vector data memeber
 * @return The pointer to the object member: "myCardSet" which can be modified
*/
template<typename R, typename S>
std::vector<Card<R, S> > CardSet<R, S>::* CardSet<R, S>::getSetPtr()
{
	return &CardSet<R, S>::myCardSet;
}

/**
 * @brief Do deep copy
 * @param other the object you want to copy
*/
template<typename R, typename S>
CardSet<R, S>::CardSet(const CardSet<R, S>& other)
{
	myCardSet = other.myCardSet;
}

