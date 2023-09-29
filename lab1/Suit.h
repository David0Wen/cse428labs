/*
// File: Suit.h
// Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
// Purpose: Declaration of enum class: Suit
*/
#ifndef _SUIT_H
#define _SUIT_H
#include <iostream>

// declare an enumerated type for the different suits
enum class Suit
{
	clubs, diamonds, hearts, spades, undefined
};

// shift operator declaration
// Output the suit feature to std::ostream
// @param std::ostream & the stream you want to output to
// @param const Suit& the object you want to output
// @return std::ostream &
std::ostream &operator<<(std::ostream&, const Suit&);

// define operators ++ for Suit
// iterate the Suit to the next
// @param Suit& the object you want to increase
// @return Suit &
Suit &operator++(Suit&);

#endif