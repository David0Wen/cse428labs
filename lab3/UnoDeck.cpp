#include "UnoDeck.h"

/** 
 * @brief implentation operators << for UnoRank, Output the UnoRank to std::ostream
 * @param os the stream you want to output to
 * @param rank the object you want to output
 * @return the reference of the input ostream
 */
std::ostream& operator<<(std::ostream& os, UnoRank rank){
    os << rank;
    return os;
}

/** 
 * @brief implentation operators ++ for UnoRank, iterate the UnoRank to the next
 * @param rank the object you want to increase
 * @return the reference of the UnoRank after increase
 */
UnoRank operator++(UnoRank& rank){
    switch(rank){
        case UnoRank::one:
            rank = UnoRank::two;
            break;
        case UnoRank::two:
            rank = UnoRank::three;
            break;
        case UnoRank::three:
            rank = UnoRank::four;
            break;
        case UnoRank::four:
            rank = UnoRank::five;
            break;
        case UnoRank::five:
            rank = UnoRank::six;
            break;
        case UnoRank::six:
            rank = UnoRank::seven;
            break;
        case UnoRank::seven:
            rank = UnoRank::eight;
            break;
        case UnoRank::eight:
            rank = UnoRank::nine;
            break;
        case UnoRank::nine:
            break;
    }
    return rank;
}

/** 
 * @brief implentation operators << for Color, Output the Color to std::ostream
 * @param os the stream you want to output to
 * @param color the object you want to output
 * @return the reference of the input ostream
 */
std::ostream& operator<<(std::ostream& os, Color color){
    os << color;
    return os;
}

/** 
 * @brief implentation operators ++ for Color, iterate the Color to the next
 * @param color the object you want to increase
 * @return the reference of the color after increase
 */
Color operator++(Color& color){
    switch(color){
        case Color::red:
            color = Color::blue;
            break;
        case Color::blue:
            color = Color::green;
            break;
        case Color::green:
            color = Color::yellow;
            break;
        case Color::yellow:
            color = Color::black;
            break;
        // remain the same
        case Color::black:
            break;
    }
    return color;
}

// Default constructor for the UnoDeck class
// Initializes the deck with 112 cards
// 1. One red, one blue, one green, and one yellow card of rank zero;
// 2. Two red, two blue, two green, and two yellow cards of each rank one through drawtwo;
// 3. Four black cards of each rank drawfour through blank
UnoDeck::UnoDeck(/* args */)
{
    myCardSet.push_back(Card(UnoRank::zero, Color::red));
    myCardSet.push_back(Card(UnoRank::zero, Color::blue));
    myCardSet.push_back(Card(UnoRank::zero, Color::green));
    myCardSet.push_back(Card(UnoRank::zero, Color::yellow));

    for (UnoRank i = UnoRank::one; i != UnoRank::drawfour; ++i)
    {
        for (Color j = Color::red; j != Color::black; ++j)
        {
            myCardSet.push_back(Card(i, j));
            myCardSet.push_back(Card(i, j));
        }
    }

    for (UnoRank i = UnoRank::one; i != UnoRank::drawfour; ++i)
    {
        myCardSet.push_back(Card(i, Color::black));   
        myCardSet.push_back(Card(i, Color::black));  
        myCardSet.push_back(Card(i, Color::black));  
        myCardSet.push_back(Card(i, Color::black));  
    }
}
