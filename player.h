#ifndef PLAYER_H
#define PLAYER_H
#include<set>
#include<iostream>
#include<vector>
#include "hand.h"

using namespace std;

class Table; 

class Player
{
private:
    int id;
    vector<pair<int, int>> starting;
    Hand fullhands;

public:
    Player(Table& T);
    void insertStarting(const pair<int, int>& card);
    void insertFullhands(const pair<int, int>& card);

    pair<int, pair<int, int>> computeRank() const;
  
    static int idcnt;
};

#endif