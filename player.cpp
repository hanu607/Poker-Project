#include "player.h"
#include "table.h"

Player::Player() : cur_size(0){};
void Player::insertHand(const std::pair<int, int> &card)
{
    hand[cur_size++] = card;
}
std::array<std::pair<int, int>, 2> Player::getHand() const
{
    return hand;
}
