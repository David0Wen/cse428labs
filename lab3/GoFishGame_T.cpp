#include "GoFishGame_T.h"

template <typename S, typename R, typename D>
const std::vector<std::string> GoFishGame<S, R, D>::rankInstructions = {
    "For HoldEm Deck, rank is 2, 3, 4, 5, 6, 7, 8, 9,\n10, J, Q, K, A; corresponding rank number is 0-12.",
    "For Pinochle Deck, rank is 9, J, Q, K,\n10, A; corresponding rank number is 0-5.",
    "For Uno Deck, rank is 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, Skip, Reverse,\nDrawTwo, DrawFour, Wild, Blank; corresponding rank number is 0-15."
};

// template specialization for HoldEmDeck
template<>
GoFishGame<Suit, HoldEmRank, HoldEmDeck>::GoFishGame(int argc, const char* argv[]) : Game(argc - 1, argv) {
    deckID = 0;
    numPlayers = playerNames.size();
    myDeck = HoldEmDeck();
    playerHands.resize(numPlayers);
    playerBooks.resize(numPlayers);
    playerBooksNum.resize(numPlayers);
    for (auto currentRank = HoldEmRank::two; currentRank < HoldEmRank::undefined; ++currentRank) {
        int count = std::count_if(myDeck.begin(), myDeck.end(),
            [currentRank](const auto& card) { return card.myRank == currentRank; });

        if (count < 4) {
            throw std::invalid_argument("Invalid deck: Must have at least 4 cards of each rank.");
        }
    }
}

// template specialization for PinochleDeck
template<>
GoFishGame<Suit, PinochleRank, PinochleDeck>::GoFishGame(int argc, const char* argv[]) : Game(argc - 1, argv) {
    deckID = 1;
    numPlayers = playerNames.size();
    myDeck = PinochleDeck();
    playerHands.resize(numPlayers);
    playerBooks.resize(numPlayers);
    playerBooksNum.resize(numPlayers);
    for (auto currentRank = PinochleRank::nine; currentRank < PinochleRank::undefined; ++currentRank) {
        int count = std::count_if(myDeck.begin(), myDeck.end(),
            [currentRank](const auto& card) { return card.myRank == currentRank; });

        if (count < 4) {
            throw std::invalid_argument("Invalid deck: Must have at least 4 cards of each rank.");
        }
    }
}

// template specialization for UnoDeck
template<>
GoFishGame<Color, UnoRank, UnoDeck>::GoFishGame(int argc, const char* argv[]) : Game(argc - 1, argv) {
    deckID = 2;
    numPlayers = playerNames.size();
    myDeck = UnoDeck();
    playerHands.resize(numPlayers);
    playerBooks.resize(numPlayers);
    playerBooksNum.resize(numPlayers);
    for (auto currentRank = UnoRank::zero; currentRank < UnoRank::undefined; ++currentRank) {
        int count = std::count_if(myDeck.begin(), myDeck.end(),
            [currentRank](const auto& card) { return card.myRank == currentRank; });

        if (count < 4) {
            throw std::invalid_argument("Invalid deck: Must have at least 4 cards of each rank.");
        }
    }
}

/** 
 * @brief  checks if there is a 4-of-a-kind in that player's hand 
 * @param playerNum the index of the palyer
 * @return a boolean value to indicate whether or not 4 cards of the same rank were found in it
 */
template<typename S, typename R, typename D>
bool GoFishGame<S, R, D>::collect_books(int playerNum) {
    auto& hand = playerHands[playerNum - 1];
    // Start from 0 (cast to R) and iterate until the rank before 'undefined'
    for (R rank = static_cast<R>(0); rank < R::undefined; ++rank) {
        size_t count = std::count_if(hand.begin(), hand.end(), [rank](const Card<R, S>& card) {
            return card.myRank == rank;
            });

        if (count == 4) {
            // Collect all cards of this rank
            auto predicate = [rank](const Card<R, S>& card) { return card.myRank == rank; };
            playerBooks[playerNum - 1].collect_if(hand, predicate);
            playerBooksNum[playerNum - 1] += 1;
            return true;
        }
    }
    return false;
}

/** 
 * @brief  implements how each player will take their turn
 * @param playerNum the index of the palyer
 * @return a boolean value to indicate whether it still remains that player's turn
 */
template <typename S, typename R, typename D>
bool GoFishGame<S, R, D>::turn(int playerNum)
{
    for (size_t i = 0; i < playerNames.size(); i++)
    {
        std::cout << "Player " << playerNames[i] << ", ID: " << i + 1 << std::endl;
        std::cout << "Current hand: " << std::endl;
        for (auto iter = playerHands[i].begin(); iter != playerHands[i].end(); ++iter) {
            std::cout << *iter << " ";
        }
        std::cout << std::endl << std::endl;

        std::cout << "Current book: " << std::endl;
        if (playerBooksNum[i] == 0) {
            std::cout << "No book collected." << std::endl << std::endl;
        }
        else {
            R curRank = (*(playerBooks[i].begin())).myRank;
            for (auto iter = playerBooks[i].begin(); iter != playerBooks[i].end(); ++iter) {
                if (curRank != (*iter).myRank)
                {
                    std::cout << std::endl;
                    curRank = (*iter).myRank;
                }
                std::cout << *iter << " ";
            }
            std::cout << std::endl << std::endl;
        }
    }
    std::cout << std::endl << "Player " << playerNames[playerNum - 1] << "'s turn. ID: " << playerNum << std::endl;

    std::cout << std::endl << rankInstructions[deckID] << std::endl << std::endl;
    int targetPlayer;
    int requestedRank;
    bool validInput = false;
    while (!validInput) {
        std::cout << "Enter card rank number to ask for: ";
        while (!(std::cin >> requestedRank)) {
            std::cout << "Integer required! Please enter again:";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Enter player ID to ask from: ";
        while (!(std::cin >> targetPlayer)) {
            std::cout << "Integer required! Please enter again:";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Do sanity check
        bool validRank = false;
        for (auto iter = playerHands[playerNum - 1].begin(); iter != playerHands[playerNum - 1].end(); ++iter) {
            if (static_cast<int>((*iter).myRank) == requestedRank)
            {
                validRank = true;
                break;
            }
        }
        if (!validRank) {
            std::cout << "Invalid Rank Number!" << std::endl;
            validInput = false;
        }
        else {
            validInput = true;
        }

        if (targetPlayer < 1 || targetPlayer > numPlayers || targetPlayer == playerNum) {
            std::cout << "Invalid Player ID!" << std::endl;
            validInput = false;
        }
    }

    // Request logic
    bool gotCard = playerHands[playerNum - 1].request(playerHands[targetPlayer - 1], static_cast<R>(requestedRank));
    if (gotCard) {
        std::cout << "Successfully Collected!" << std::endl;
        while (collect_books(playerNum)) { /* Collect any possible books */ }
        std::cout << std::endl;
        return true; // Player gets another turn
    }
    else {
        // Go fish: Draw a card from the deck
        if (!myDeck.is_empty()) {
            std::cout << "Collection Failed! Draw a card from the deck." << std::endl;
            myDeck >> playerHands[playerNum - 1];
            std::cout << std::endl;
            return (*(--playerHands[playerNum - 1].end())).myRank == static_cast<R>(requestedRank);
        }
        else
        {
            std::cout << "Collection Failed and deck is empty! You're out." << std::endl;
            outPlayers.push_back(playerNum);
            myDeck.collect(playerHands[playerNum - 1]);
            std::cout << std::endl;
            return false;
        }
    }
}

template<typename S, typename R, typename D>
void GoFishGame<S, R, D>::deal() {
    myDeck.shuffle();
    int cardsPerPlayer = (numPlayers > 2) ? 5 : 7;

    for (int i = 0; i < cardsPerPlayer; ++i) {
        for (auto& hand : playerHands) {
            if (!myDeck.is_empty()) {
                myDeck >> hand;
            }
        }
    }
}

template<typename S, typename R, typename D>
int GoFishGame<S, R, D>::play() {
    deal(); // Deal cards to players

    for (int i = 1; i <= numPlayers; ++i) {
        while (collect_books(i)) { /* Collect any possible books */ }
    }

    bool gameOn = true;
    int roundNumber = 0;
    while (gameOn) {
        for (int i = 1; i <= numPlayers; ++i) {
            if (std::any_of(outPlayers.begin(), outPlayers.end(), [i](int player) { return player == i; }))
            {
                continue;
            }
            while (turn(i)) { /* Turn for a player until they fail */ }
        }
        std::cout << "End of Round " << ++roundNumber << std::endl;
        for (int i = 1; i <= numPlayers; ++i) {
            std::cout << "Player " << playerNames[i - 1] << ", ID: " << i << std::endl;
            std::cout << "Number of books collected: " << playerBooksNum[i - 1] << std::endl;

        }
        bool handsEmpty = true;
        for (int i = 1; i <= numPlayers; ++i) {
            if (!playerHands[i - 1].is_empty())
            {
                handsEmpty = false;
                break;
            }
        }
        if ((myDeck.is_empty() && handsEmpty) || numPlayers - outPlayers.size() < 2)
        {
            gameOn = false;
        }
    }
    
    int max_value = *std::max_element(playerBooksNum.begin(), playerBooksNum.end());

    std::vector<int> max_indices;
    for (size_t i = 0; i < playerBooksNum.size(); ++i) {
        if (playerBooksNum[i] == max_value) {
            max_indices.push_back(i);
        }
    }

    std::cout << "Game End! Players: ";
    for (auto index : max_indices) {
        std::cout << playerNames[index] << " ";
    }
    std::cout << "collected the most books!";
    return 0;
}
