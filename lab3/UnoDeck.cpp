#include "UnoDeck.h"

/** 
 * @brief implentation operators << for UnoRank, Output the UnoRank to std::ostream
 * @param os the stream you want to output to
 * @param rank the object you want to output
 * @return the reference of the input ostream
 */
std::ostream &operator<<(std::ostream &os, const UnoRank &rank) {
    switch (rank) {
        // Handle each UnoRank case, converting it to a string
        case UnoRank::zero: os << "0"; break;
        case UnoRank::one: os << "1"; break;
        case UnoRank::two: os << "2"; break;
        case UnoRank::three: os << "3"; break;
        case UnoRank::four: os << "4"; break;
        case UnoRank::five: os << "5"; break;
        case UnoRank::six: os << "6"; break;
        case UnoRank::seven: os << "7"; break;
        case UnoRank::eight: os << "8"; break;
        case UnoRank::nine: os << "9"; break;
        case UnoRank::skip: os << "Skip"; break;
        case UnoRank::reverse: os << "Reverse"; break;
        case UnoRank::drawtwo: os << "DrawTwo"; break;
        case UnoRank::drawfour: os << "DrawFour"; break;
        case UnoRank::wild: os << "Wild"; break;
        case UnoRank::blank: os << "Blank"; break;
        default: os << "?"; break;
    }
    return os;
}

/** 
 * @brief implentation operators ++ for UnoRank, iterate the UnoRank to the next
 * @param rank the object you want to increase
 * @return the reference of the UnoRank after increase
 */
UnoRank &operator++(UnoRank &rank) {
    if (rank == UnoRank::undefined) {
        // If already undefined, remain unchanged
        return rank;
    }
    // Increment to the next rank, or to undefined if at the last valid rank
    rank = static_cast<UnoRank>(static_cast<int>(rank) + 1);
    return rank;
}

/** 
 * @brief implentation operators << for Color, Output the Color to std::ostream
 * @param os the stream you want to output to
 * @param color the object you want to output
 * @return the reference of the input ostream
 */
std::ostream &operator<<(std::ostream &os, const Color &color) {
    switch (color) {
        case Color::red: os << "Red"; break;
        case Color::blue: os << "Blue"; break;
        case Color::green: os << "Green"; break;
        case Color::yellow: os << "Yellow"; break;
        case Color::black: os << "Black"; break;
        default: os << "?"; break;
    }
    return os;
}

/** 
 * @brief implentation operators ++ for Color, iterate the Color to the next
 * @param color the object you want to increase
 * @return the reference of the color after increase
 */
Color &operator++(Color &color) {
    if (color == Color::undefined) {
        // If already undefined, remain unchanged
        return color;
    }
    // Increment to the next color, or to undefined if at the last valid color
    color = static_cast<Color>(static_cast<int>(color) + 1);
    return color;
}

// Default constructor for the UnoDeck class
// Initializes the deck with 112 cards
// 1. One red, one blue, one green, and one yellow card of rank zero;
// 2. Two red, two blue, two green, and two yellow cards of each rank one through drawtwo;
// 3. Four black cards of each rank drawfour through blank
UnoDeck::UnoDeck()
{
    for (Color i = Color::red; i != Color::black; ++i)
    {
        Card<UnoRank, Color> myCard(UnoRank::zero, i);
        myCardSet.push_back(myCard);
    }

    for (UnoRank i = UnoRank::one; i != UnoRank::drawfour; ++i)
    {
        for (Color j = Color::red; j != Color::black; ++j)
        {
            for (int cnt = 0; cnt < 2; ++cnt)
            {
                Card<UnoRank, Color> myCard(i, j);
                myCardSet.push_back(myCard);
            }
        }
    }

    for (UnoRank i = UnoRank::drawfour; i != UnoRank::undefined; ++i)
    {
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            Card<UnoRank, Color> myCard(i, Color::black);
            myCardSet.push_back(myCard);
        }
    }
}
