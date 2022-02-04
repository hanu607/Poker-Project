#include "enum.h"
#include "table.h"
#include "function.h"
#include <algorithm>

Table::Table() : deck{}, res{}, cur_size(0)
{
    int n = 2;
    while (n--)
        appendPlayer();
};
void Table::appendPlayer()
{
    players.push_back(Player());
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
std::array<int, 6> Table::computeRank(const Player &p) const
{
    int suits[4] = {};
    int nums[15] = {};
    std::array<std::pair<int, int>, 8> hand;
    {
        const auto &temp = p.getHand();
        std::copy(temp.cbegin(), temp.cend(), hand.begin());
        std::copy(community.cbegin(), community.cend(), hand.begin() + 2);
    }

    std::sort(hand.begin(), hand.end(), [](const auto &lhs, const auto &rhs) -> bool
              { return lhs.second > rhs.second; });
    for (int i = 0; i < 7; i++)
    {
        suits[hand[i].first]++;
        nums[hand[i].second]++;
    }

    std::array<int, 6> rank;
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
    const auto &rank0 = computeRank(players[0]);
    const auto &rank1 = computeRank(players[1]);
    return rank0 == rank1 ? 0 : (rank0 > rank1 ? 1 : -1);
}
