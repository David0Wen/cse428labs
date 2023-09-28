#include "Deck_T.h"

template<typename R, typename S>
void Deck<R, S>::shuffle()
{
    std::random_device deviceGenerator;
    std::mt19937 numGenerator(deviceGenerator());
    std::shuffle(CardSet<R, S>::myCardSet.begin(), CardSet<R, S>::myCardSet.end(), numGenerator);
}