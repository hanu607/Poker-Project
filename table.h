#ifndef TABLE_H
#define TABLE_H
#include "player.h"
#include <vector>
#include <tuple>

class Table
{
private:
    bool deck[4][15];
    std::vector<Player> players;
    std::vector<std::pair<int, int>> community;
    int cur_size;
    int res[3];

public:
    Table();
    void appendPlayer();
    void insertHand(const int &i, const std::pair<int, int> &card);
    void insertCommunity(const std::pair<int, int> &card);
    std::vector<int> computeRank(const Player &p) const;
    int Showdown() const;

    friend int* Bruteforce(Table& T);
    friend void bfSuit(Table& T, int k);
    friend void bfNum(Table& T, int k);
};

#endif
