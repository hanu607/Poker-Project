#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

class Table;

class Player
{
private:
    int id;
    std::vector<std::pair<int, int>> hand;

public:
    Player() : id(idcnt++){};
    void insertHand(const std::pair<int, int> &card);
    std::vector<std::pair<int, int>> getHand() const;

    static int idcnt;
};

#endif
