#include "enum.h"
#include "player.h"

Player::Player() : cur_size(0), rank{}, result{} {};
void Player::insertStarting(const std::pair<int, int> card)
{
    starting[cur_size++] = card;
}
