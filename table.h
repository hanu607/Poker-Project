#ifndef TABLE_H
#define TABLE_H
#include "player.h"
#include <vector>
#include <array>

class Table
{
private:
    bool deck[4][15];
    std::vector<Player> players;
    std::array<std::pair<int, int>, 5> community;
    int cur_size;
    int res[3];

public:
    Table();
    void appendPlayer();
    void insertHand(const int &i, const std::pair<int, int> &card);
    void insertCommunity(const std::pair<int, int> &card);
    std::array<int, 6> computeRank(const Player &p) const;
    int Showdown() const;

    friend int *bruteforce(Table &T);
    friend void backtracking(Table &T, const int &k);
};

#endif
