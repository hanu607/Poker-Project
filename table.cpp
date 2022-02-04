#include "enum.h"
#include "table.h"
#include "function.h"
#include <algorithm>
#include <deque>

Table::Table() : deck{}, community(5, {0, 0}), res{}, cur_size(0)
{
    int n = 2;
    while (n--)
        appendPlayer();
};

void Table::appendPlayer()
{
    Player p;
    players.push_back(p);
}
void Table::insertHand(const int &i, const std::pair<int, int> &card)
{
    players[i].insertHand(card);
    deck[card.first][card.second] = true;
}
void Table::insertCommunity(const std::pair<int, int> &card)
{
    community[cur_size++] = card;
    deck[card.first][card.second] = true;
}
std::vector<int> Table::computeRank(const Player &p) const
{
    int suits[4] = {};
    int nums[15] = {};
    std::vector<std::pair<int, int>> hand(p.getHand());
    hand.insert(hand.end(), community.begin(), community.end());

    std::sort(hand.begin(), hand.end(), [](const auto &lhs, const auto &rhs) -> bool
              { return lhs.second >= rhs.second; });
    for (const auto &card : hand)
    {
        const auto &[s, n] = card;
        suits[s]++;
        nums[n]++;
    }

    std::vector<int> rank;
    if (rank = isFlush(hand, suits); !rank.front())
    {
        if (rank = isStraight(hand); !rank.front())
            return isPairs(nums);
        return rank;
    }
    return rank;
}

int Table::Showdown() const
{
    const auto& rank0 = computeRank(players[0]);
    const auto& rank1 = computeRank(players[1]);
    return rank0 == rank1 ? 0 : (rank0 > rank1 ? 1 : -1);
}
