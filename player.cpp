#include "player.h"
#include "table.h"

void Player::insertHand(const std::pair<int, int> &card)
{
    hand.push_back(card);
};
std::vector<std::pair<int, int>> Player::getHand() const
{
    return hand;
}
int Player::idcnt = 0;
