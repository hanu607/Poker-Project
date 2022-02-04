#include "player.h"
#include "table.h"

Player::Player() : id(idcnt++), hand(2, {0, 0}), cur_size(0){};
void Player::insertHand(const std::pair<int, int> &card)
{
    hand[cur_size++] = card;
}
std::vector<std::pair<int, int>> Player::getHand() const
{
    return hand;
}
int Player::idcnt = 0;
