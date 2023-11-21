#include "GoFishGame_T.h"


template<>
GoFishGame<Suit, HoldEmRank,HoldEmDeck>::GoFishGame(int numPlayers, const char* playerNames[]){
    for (int i = static_cast<int>(HoldEmRank::two); i < static_cast<int>(HoldEmRank::undefined); ++i) {
        HoldEmRank currentRank = static_cast<HoldEmRank>(i);
        int count = std::count_if(deck.begin(), deck.end(),
            [currentRank](const auto& card) { return card.getRank() == currentRank; });

        if (count < 4) {
            throw std::invalid_argument("Invalid deck: Must have at least 4 cards of each rank.");
        }
    }
}

template<>
GoFishGame<Suit, PinochleRank,PinochleDeck>::GoFishGame(int numPlayers, const char* playerNames[]){
    for (int i = static_cast<int>(PinochleRank::nine); i < static_cast<int>(PinochleRank::undefined); ++i) {
        PinochleRank currentRank = static_cast<PinochleRank>(i);
        int count = std::count_if(deck.begin(), deck.end(),
            [currentRank](const auto& card) { return card.getRank() == currentRank; });

        if (count < 4) {
            throw std::invalid_argument("Invalid deck: Must have at least 4 cards of each rank.");
        }
    }
}

template<>
GoFishGame<Color, UnoRank, UnoDeck>::GoFishGame(int numPlayers, const char* playerNames[]){
    for (int i = static_cast<int>(UnoRank::zero); i < static_cast<int>(UnoRank::undefined); ++i) {
        UnoRank currentRank = static_cast<UnoRank>(i);
        int count = std::count_if(deck.begin(), deck.end(),
            [currentRank](const auto& card) { return card.getRank() == currentRank; });

        if (count < 4) {
            throw std::invalid_argument("Invalid deck: Must have at least 4 cards of each rank.");
        }
    }
}

template <typename S, typename R, typename D>
bool GoFishGame<S, R, D>::collect_books(int playerNum){
    if (playerNum < 0 || playerNum >= numPlayers) {
            throw std::out_of_range("Invalid player number");
        }

    for (const auto& card : hands[playerNumber]) {
        auto predicate = [card](const Card<Suit, Rank>& c) {
            return c.getRank() == card.getRank();
        }
        if (hands[playerNumber].count_if(card) == 4) {
            books[playerNumber].collect_if(hands[playerNumber], predicate);

            return true;
            }
    }

    template <typename S, typename R, typename D>
    bool GoFishGame<S, R, D>::turn(int playerNum)
    {
        std::cout << "Player "<< playerNum << "'s turn."
        std::cout << "Current hand: "<< hands[playerNum] << std::endl;
        std::cout << "Current book: " << books[playerNum] << std::endl;

        std::cout << "Enter the card rank to ask for: ";
        Rank requestedRank;
        std::cin >> requestedRank;
        
        std::cout << "Enter the player number to ask from: ";
        int targetPlayer;
        std::cin >> targetPlayer;


        return false;
    }

    return false; // No 4 cards of the same rank found
}
