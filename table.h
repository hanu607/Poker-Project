#ifndef TABLE_H
#define TABLE_H
#include "player.h"
#include <vector>

class Table
{
private:
    std::vector<Player> players;
    std::vector<std::pair<int, int>> community;

public:
    Table(int n = 2)
    {
        if (n < 2)
            n = 2;
        while (n--)
            appendPlayer();
    };
    void appendPlayer();
    void insertHand(const int &i, const std::pair<int, int> &card);
    void insertCommunity(const std::pair<int, int> &card);
    std::vector<int> computeRank(const Player &p) const;
    int Showdown() const;
};

#endif
