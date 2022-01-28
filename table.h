#include "headers.h"
#include "player.h"

class Table
{
private:
    vector<Player*> players;
    vector<pair<int, int>> board;

public:
    enum Ranks
    {
        HIGHCARD,
        ONEPAIR,
        TWOPAIR,
        TRIPPLE,
        STRAIGHT,
        FLUSH,
        FULLHOUSE,
        FOURCARD,
        STRAIGHTFLUSH
    };

    void append_board(const pair<int, int> &card);

    void append_player(Player &p);

    pair<int, pair<int, int>> isStraight(Player &p) const;
    pair<int, pair<int, int>> isStraight(Player &p, int s) const;
    pair<int, pair<int, int>> isFlush(Player &p) const;
    pair<int, pair<int, int>> isPairs(Player &p) const;
    pair<int, pair<int, int>> computeRank(Player &p) const;

    bool Showdown();
};
