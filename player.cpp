#include "player.h"
#include "table.h"

Player::Player(Table &T) : id(++idcnt), nums{}, suits{}
{
    T.append_player(*this);
}

void Player::append_hand(const pair<int, int> &card)
{
    this->hands.insert(card);
    auto [s, n] = card;
    this->nums[n]++;
    this->suits[s]++;
    if (n == A)
        nums[1]++;
};

int Player::idcnt = 0;
