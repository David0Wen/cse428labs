#include "Deck_T.h"

template<typename R, typename S>
void Deck<R, S>::shuffle()
{
    std::random_device deviceGenerator;
    std::mt19937 numGenerator(deviceGenerator());
    std::shuffle(CardSet<R, S>::myCardSet.begin(), CardSet<R, S>::myCardSet.end(), numGenerator);
}

template <typename R, typename S>
void Deck<R, S>::collect(CardSet<R, S>& cardSet)
{
    if (!cardSet.is_empty())
    {
        this->myCardSet.insert(this->myCardSet.end(), cardSet.myCardSet.begin(), cardSet.myCardSet.end());
        cardSet.myCardSet.clear();
    }
}
