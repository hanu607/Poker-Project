#include "enum.h"
#include "function.h"
#include "table.h"
#include <algorithm>
#include <deque>

std::vector<int> isStraight(std::vector<std::pair<int, int>> &hand)
{
    if (hand.front().second == A)
        hand.push_back({-1, 1});
    std::vector<int> ret(1);
    std::deque<int> dq;
    for (const auto &card : hand)
    {
        if (!dq.empty() && dq.back() - 1 != card.second)
            dq.clear();
        dq.push_back(card.second);
        if (dq.size() == 5)
        {
            ret[0] = STRAIGHT;
            ret.push_back(dq.front());
            break;
        }
    }
    if (hand.back().second == 1)
        hand.pop_back();
    return ret;
};

std::vector<int> isStraightFlush(std::vector<std::pair<int, int>> &hand, const int &s)
{
    std::vector<int> ret(1);
    std::deque<int> dq;
    for (int i = 0; i < hand.size(); i++)
    {
        const auto &card = hand[i];
        if (card.first != s)
            continue;
        if (card.second == A)
            hand.push_back({s, 1});
        if (!dq.empty() && dq.back() - 1 != card.second)
            dq.clear();
        dq.push_back(card.second);
        if (dq.size() == 5)
        {
            ret[0] = STRAIGHTFLUSH;
            ret.push_back(dq.front());
            break;
        }
    }
    if (hand.back().second == 1)
        hand.pop_back();
    return ret;
};

std::vector<int> isFlush(std::vector<std::pair<int, int>> &hand, int suits[])
{
    std::vector<int> ret(1);
    for (int s = SPADE; s <= DIAMOND; s++)
    {
        if (suits[s] < 5)
            continue;
        ret[0] = FLUSH;
        for (const auto &card : hand)
            if (card.first == s)
            {
                ret.push_back(card.second);
                break;
            }

        if (const auto &tmp = isStraightFlush(hand, s); tmp[0])
        {
            ret = tmp;
            break;
        }
    }
    return ret;
};

std::vector<int> isPairs(int nums[])
{
    std::vector<int> ret(1);
    std::vector<std::pair<int, int>> arr;
    for (int n = A; n > 1; n--)
        if (nums[n])
            arr.push_back({n, nums[n]});

    sort(arr.begin(), arr.end(),
         [](const auto &lhs, const auto &rhs) -> bool
         {
             if (lhs.second == rhs.second)
                 return lhs.first > rhs.first;
             return lhs.second > rhs.second;
         });

    int append = 1;
    if (arr[0].second == 4)
    {
        ret[0] = FOUROFAKIND;
        append = 2;
    }
    else if (arr[0].second == 3)
    {
        if (arr[1].second > 1)
        {
            ret[0] = FULLHOUSE;
            append = 2;
        }
        else
        {
            ret[0] = THREEOFAKIND;
            append = 3;
        }
    }
    else if (arr[0].second == 2)
    {
        if (arr[1].second == 2)
        {
            ret[0] = TWOPAIRS;
            append = 3;
        }
        else
        {
            ret[0] = ONEPAIR;
            append = 4;
        }
    }
    else
    {
        ret[0] = HIGHCARD;
        append = 5;
    }

    for (int i = 0; i < append; i++)
        ret.push_back(arr[i].first);

    return ret;
};

// int wins = 0;
// int ties = 0;
// int loses = 0;
// double odds = 0;

int* Bruteforce(Table &T)
{
    bfSuit(T, T.cur_size);
    // odds = (wins / (double)(wins + ties + loses))*100;
    return T.res;
}
void bfSuit(Table &T, int k)
{
    if (k == 5)
    {
        bfNum(T, T.cur_size);
        return;
    }

    int st = k > T.cur_size ? T.community[k - 1].first : 0;
    for (int s = st; s <= DIAMOND; s++)
    {
        T.community[k].first = s;
        bfSuit(T, k + 1);
    }
}
void bfNum(Table &T, int k)
{
    if (k == 5)
    {
        T.res[T.Showdown() + 1]++;
        // switch (T.Showdown())
        // {
        // case 1:
        //     wins++;
        //     break;
        // case 0:
        //     ties++;
        //     break;
        // case -1:
        //     loses++;
        //     break;
        // }
        return;
    }

    int st = (k > T.cur_size && T.community[k - 1].first == T.community[k].first) ? T.community[k - 1].second + 1 : 2;
    for (int n = st; n <= A; n++)
    {
        if (T.deck[T.community[k].first][n])
            continue;
        T.community[k].second = n;
        bfNum(T, k + 1);
    }
}
