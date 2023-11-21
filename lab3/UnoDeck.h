/**
 * File: UnoDeck.h
 * Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
 * Purpose: Declaration of types related to an Uno deck
 */

#define once

#include <iostream>
// Include struct card as a member of PinochleDeck
#include "Card_T.h"
// Include base class deck, inherit the base method print
#include "Deck_T.h"

// Declare Uno specific card colors
enum Color{
    red,
    blue,
    green,
    yellow,
    black,
    undefined
};

// Declare Uno specific card ranks
enum UnoRank{
    zero, one, two, three, four, five, six, seven, eight, nine, 
    skip, reverse, drawtwo, drawfour, wild, blank, undefined
};

// Output the UnoRank to ostream
std::ostream& operator<<(std::ostream& os, UnoRank rank);
/** 
 * @brief implentation operators ++ for UnoRank, iterate the UnoRank to the next
 * @param rank the object you want to increase
 * @return the reference of the UnoRank after increase
 */
UnoRank operator++(UnoRank& rank);

/** 
 * @brief implentation operators << for Color, Output the Color to std::ostream
 * @param os the stream you want to output to
 * @param color the object you want to output
 * @return the reference of the input ostream
 */
std::ostream& operator<<(std::ostream& os, Color color);

/** 
 * @brief implentation operators ++ for Color, iterate the Color to the next
 * @param color the object you want to increase
 * @return the reference of the color after increase
 */
Color operator++(Color& color);

// define Uno Deck derived from Deck class
class UnoDeck : public Deck<UnoRank, Color>
{
private:
    /* data */
public:
    // default constructor
    UnoDeck(/* args */);
    ~UnoDeck() = default;
};

