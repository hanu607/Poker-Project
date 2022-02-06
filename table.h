#ifndef TABLE_H
#define TABLE_H
#include "player.h"
#include <vector>
#include <array>

class Table
{
private:
    std::array<std::array<int, 15>, 4> deck;
    std::vector<Player> players;
    std::array<std::pair<int, int>, 5> community;
    int cur_size;

public:
    Table();
    void appendPlayer();
    void insertStarting(const int idx, const std::pair<int, int> card);
    void insertCommunity(const std::pair<int, int> card);
    std::pair<double, double> getResult(const int idx);
    
    void bruteforce();
    void backtracking(const int k);
    void computeRank(const int idx);
    void showdown();
};

#endif
