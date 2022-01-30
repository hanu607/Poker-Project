#include "table.h"

void Table::insertCommunity(const std::pair<int, int> &card)
{
    community.push_back(card);
    for (Player *it : players)
        (*it).insertFullhands(card);
}
void Table::appendPlayer(Player &p)
{
    players.push_back(&p);
}
bool Table::Showdown() const
{
    return (*this->players[0]).computeRank() > (*this->players[1]).computeRank();
}
