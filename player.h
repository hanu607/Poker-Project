#ifndef PLAYER_H
#define PLAYER_H
#include <array>

class Player
{
private:
    std::array<std::pair<int, int>, 2> hand;
    int cur_size;

public:
    Player();
    void insertHand(const std::pair<int, int> &card);
    std::array<std::pair<int, int>, 2> getHand() const;
};

#endif
