/**
 * File: Suit.h
 * Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
 * Purpose: Declaration of enum class: Suit
 */
#ifndef _SUIT_H
#define _SUIT_H
#include <iostream>

// declare an enumerated type for the different suits
enum class Suit
{
    clubs, diamonds, hearts, spades, undefined
};

/**
 * @brief shift operator implentation, Output the suit feature to std::ostream
 * @param os the stream you want to output to
 * @param const Suit& the object you want to output
 * @return the reference of the inupt ostream
 */
std::ostream &operator<<(std::ostream &, const Suit &);

/**
 * @brief Implenment operators ++ for Suit, iterate the Suit to the next
 * @param mySuit the object you want to increase
 * @return the reference after increase
 */
Suit &operator++(Suit &);

#endif