#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include "player.h"
#include <vector>

using namespace std;

class Table
{
private:
    vector<Player*> players;
    vector<pair<int, int>> community;

public:
    void insertCommunity(const pair<int, int>& card);
    void appendPlayer(Player& p);

    bool Showdown();
};
#endif