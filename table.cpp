#include "enum.h"
#include "table.h"
#include "function.h"
#include <algorithm>
#include <iostream>

Table::Table() : deck{}, cur_size(0)
{
    int n = 2;
    while (n--)
        appendPlayer();
};
void Table::appendPlayer()
{
    players.push_back(Player());
}
void Table::insertStarting(const int idx, const std::pair<int, int> card)
{
    players[idx].insertStarting(card);
    deck[card.first][card.second] = true;
}
void Table::insertCommunity(const std::pair<int, int> card)
{
    community[cur_size++] = card;
    deck[card.first][card.second] = true;
}
std::pair<double, double> Table::getResult(const int idx)
{
    double total = players[idx].result[0] + players[idx].result[1] + players[idx].result[2];
    return {players[idx].result[0] / total, players[idx].result[1] / total};
}

void Table::bruteforce()
{   
    for (auto &player : players)
        std::fill(player.result.begin(), player.result.end(), 0);
    backtracking(cur_size);
};
void Table::backtracking(const int k)
{
    if (k == 5)
    {
        for (int i = 0; i < players.size(); i++)
            computeRank(i);
        showdown();
        return;
    }

    int s_start = k > cur_size ? community[k - 1].first : 0;
    for (int s = s_start; s <= DIAMOND; s++)
    {
        int n_start = (k > cur_size && community[k - 1].first == s) ? community[k - 1].second - 1 : A;
        for (int n = n_start; n >= 2; n--)
        {
            if (deck[s][n])
                continue;
            community[k] = {s, n};
            backtracking( k + 1);
        }
    }
}
void Table::computeRank(const int idx)
{
    int suits[4] = {};
    int nums[15] = {};
    int deck[4][15] = {};
    for (int i = 0; i < 2; i++)
    {
        suits[players[idx].starting[i].first]++;
        nums[players[idx].starting[i].second]++;
        deck[players[idx].starting[i].first][players[idx].starting[i].second] = true;
    }
    for (int i = 0; i < 5; i++)
    {
        suits[community[i].first]++;
        nums[community[i].second]++;
        deck[community[i].first][community[i].second] = true;
    }
    nums[1] = nums[A];
    for (int s = 0; s <= DIAMOND; s++)
        deck[s][1] = deck[s][A];
    
    if (players[idx].rank = isFlush(deck, suits); !players[idx].rank.front())
        if (players[idx].rank = isStraight(nums); !players[idx].rank.front())
            players[idx].rank = isPairs(nums);
}
void Table::showdown()
{
    const auto& r0 = players[0].rank;
    const auto& r1 = players[1].rank;
    if (r0 > r1)
    {
        players[0].result[0]++;
        players[1].result[2]++;
    }
    else if (r0 == r1)
    {
        players[0].result[1]++;
        players[1].result[1]++;
    }
    else
    {
        players[0].result[2]++;
        players[1].result[0]++;
    }
}
