#ifndef PLAYER_H
#define PLAYER_H
#include "hand.h"
#include <vector>

class Table;

class Player
{
private:
    int id;
    std::vector<std::pair<int, int>> starting;
    Hand fullhands;

public:
    Player(Table &T);
    void insertStarting(const std::pair<int, int> &card);
    void insertFullhands(const std::pair<int, int> &card);

    std::pair<int, std::pair<int, int>> computeRank() const;

    static int idcnt;
};

#endif
