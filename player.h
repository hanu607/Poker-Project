#include "headers.h"

class Table;

struct cmp
{
    bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs) const
    {
        return lhs.second > rhs.second;
    }
};

class Player
{
private:
    int id;
    int nums[15];
    int suits[4];
    set<pair<int, int>, cmp> hands;

public:
    Player(Table& T);
    friend class Table;
    void append_hand(const pair<int, int> &card);

    static int idcnt;
};
