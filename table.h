#ifndef TABLE_H
#define TABLE_H
#include "player.h"
#include <vector>

class Table
{
private:
    std::vector<Player *> players;
    std::vector<std::pair<int, int>> community;

public:
    void insertCommunity(const std::pair<int, int> &card);
    void appendPlayer(Player &p);
    std::vector<int> computeRank(std::vector<std::pair<int, int>> hand) const;
    bool Showdown() const;
};
#endif
