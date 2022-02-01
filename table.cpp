#include "enum.h"
#include "table.h"
#include "function.h"
#include <algorithm>
#include <deque>

void Table::insertCommunity(const std::pair<int, int> &card)
{
    community.push_back(card);
}
void Table::appendPlayer()
{
    Player p;
    players.push_back(p);
}
void Table::insertHand(const int &i, const std::pair<int, int> &card)
{
    players[i].insertHand(card);
}
std::vector<int> Table::computeRank(const Player &p) const
{
    int suits[4] = {0};
    int nums[15] = {0};
    auto hand = p.getHand();
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
    auto rank0 = computeRank(players[0]);
    auto rank1 = computeRank(players[1]);
    return rank0 == rank1 ? 0 : (rank0 > rank1 ? 1 : -1);
}
