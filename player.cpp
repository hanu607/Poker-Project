#include "player.h"
#include "table.h"
#include "hand.h"

Player::Player(Table& T) : id(++idcnt)
{
    T.appendPlayer(*this);
}
void Player::insertStarting(const pair<int, int>& card)
{
    starting.push_back(card);
    fullhands.insert(card);
};
void Player::insertFullhands(const pair<int, int>& card)
{
    fullhands.insert(card);
}

pair<int, pair<int, int>> Player::computeRank() const
{
    auto Flush = fullhands.isFlush();
    if (Flush.first)
        return Flush;
    else
    {
        auto Straight = fullhands.isStraight();
        if (Straight.first)
            return Straight;
        else
            return fullhands.isPairs();
    }
}
int Player::idcnt = 0;