#include "player.h"
#include "table.h"
#include "hand.h"

Player::Player(Table &T) : id(++idcnt)
{
    T.appendPlayer(*this);
}
void Player::insertStarting(const std::pair<int, int> &card)
{
    starting.push_back(card);
    fullhands.insert(card);
};
void Player::insertFullhands(const std::pair<int, int> &card)
{
    fullhands.insert(card);
}
std::pair<int, std::pair<int, int>> Player::computeRank() const
{
    auto rank = fullhands.isFlush();
    if (rank.first)
        return rank;
    else
    {
        rank = fullhands.isStraight();
        if (rank.first)
            return rank;
        else
            return fullhands.isPairs();
    }
}
int Player::idcnt = 0;
