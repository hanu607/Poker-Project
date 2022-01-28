#include "table.h"

void Table::append_board(const pair<int, int> &card)
{
    board.push_back(card);
    for (Player *it : players)
        (*it).append_hand(card);
}

void Table::append_player(Player &p)
{
    players.push_back(&p);
}

pair<int, pair<int, int>> Table::isStraight(Player &p) const
{
    pair<int, pair<int, int>> rank = {0, {0, 0}};
    deque<int> dq;
    for (auto it : p.hands)
    {
        if (dq.empty() || dq.back() - 1 == it.second)
            dq.push_back(it.second);
        else
            dq.clear();
        if (dq.size() == 5)
        {
            rank.first = STRAIGHT;
            rank.second.first = dq.front();
            break;
        }
    }
    return rank;
}
pair<int, pair<int, int>> Table::isStraight(Player &p, int s) const
{
    pair<int, pair<int, int>> rank = {0, {0, 0}};
    deque<pair<int, int>> dq;
    for (auto it : p.hands)
    {
        if (it.first != s)
            continue;
        if (dq.empty() || dq.back().second - 1 == it.second)
            dq.push_back(it);
        else
            dq.clear();
        if (dq.size() == 5)
        {
            rank.first = STRAIGHT;
            rank.second.first = dq.front().first;
            break;
        }
    }
    return rank;
}
pair<int, pair<int, int>> Table::isFlush(Player &p) const
{
    pair<int, pair<int, int>> rank = {0, {0, 0}};
    for (int s = SPADE; s <= DIAMOND; s++)
    {
        if (p.suits[s] < 5)
            continue;
        rank.first = FLUSH;
        for (auto it : p.hands)
            if (it.first == s)
            {
                rank.second.first = it.second;
                break;
            }

        int high = isStraight(p, s).second.first;
        if (high == 0)
            break;
        rank.first = STRAIGHTFLUSH;
        rank.second.first = high;
    }
    return rank;
}
pair<int, pair<int, int>> Table::isPairs(Player &p) const
{
    int mx = 0;
    pair<int, pair<int, int>> rank = {0, {0, 0}};
    for (int n = A; n > 1; n--)
    {
        if (p.nums[n] == 4)
            return {FOURCARD, {n, 0}};
        else if (p.nums[n] == 3)
        {
            if (mx == 3)
            {
                rank.first = FULLHOUSE;
                rank.second.second = n;
                break;
            }
            else if (mx == 2)
            {
                rank.first = FULLHOUSE;
                rank.second.second = rank.second.first;
                rank.second.first = n;
                break;
            }
            else
            {
                rank.first = TRIPPLE;
                rank.second.first = n;
                mx = 3;
            }
        }
        else if (p.nums[n] == 2)
        {
            if (mx == 3)
            {
                rank.first = FULLHOUSE;
                rank.second.second = n;
                break;
            }
            if (mx == 2)
            {
                rank.first = TWOPAIR;
                if (rank.second.second == 0)
                    rank.second.second = n;
                else
                    break;
            }
            else
            {
                rank.first = ONEPAIR;
                rank.second.first = n;
                mx = 2;
            }
        }
        else if (p.nums[n] == 1)
        {
            if (mx == 0)
            {
                rank.first = HIGHCARD;
                rank.second.first = n;
                mx = 1;
            }
        }
    }
    return rank;
}
pair<int, pair<int, int>> Table::computeRank(Player &p) const
{
    auto Flush = isFlush(p);
    if (Flush.first)
        return Flush;
    else
    {
        auto Straight = isStraight(p);
        if (Straight.first)
            return Straight;
        else
            return isPairs(p);
    }
}

bool Table::Showdown()
{
    return this->computeRank(*players[0]) > this->computeRank(*players[1]);
}
