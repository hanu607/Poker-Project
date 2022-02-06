#ifndef PLAYER_H
#define PLAYER_H
#include <array>

class Player
{
private:
    std::array<std::pair<int, int>, 2> starting;
    int cur_size;
    std::array<int, 6> rank;
    std::array<int, 3> result;

public:
    Player();
    void insertStarting(const std::pair<int, int> card);

    friend class Table;
};

#endif
