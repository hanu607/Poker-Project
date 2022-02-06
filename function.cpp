#include "enum.h"
#include "function.h"
#include "table.h"
#include <algorithm>

std::array<int, 6> isStraight(int nums[15])
{
    std::array<int, 6> ret{};

    int head = A, tail = A;
    while (tail > 0)
    {
        if (!nums[tail--])
            head = tail;
        if (head - tail == 5)
        {
            ret[0] = STRAIGHT;
            ret[1] = head;
            break;
        }
    }
    return ret;
};
std::array<int, 6> isStraightFlush(bool deck[4][15], const int &s)
{
    std::array<int, 6> ret{};

    int head = A, tail = A;
    while (tail > 0)
    {
        if (!deck[s][tail--])
            head = tail;
        if (head - tail == 5)
        {
            ret[0] = STRAIGHTFLUSH;
            ret[1] = head;
            break;
        }
    }
    return ret;
};
std::array<int, 6> isFlush(bool deck[4][15], int suits[4])
{
    std::array<int, 6> ret{};
    for (int s = SPADE; s <= DIAMOND; s++)
    {
        if (suits[s] < 5)
            continue;
        ret[0] = FLUSH;
        int pos = 1;
        for (int n = A; n > 0; n--)
        {
            if (deck[s][n])
                ret[pos++] = n;
            if (pos > 5)
                break;
        }

        if (const auto &tmp = isStraightFlush(deck, s); tmp.front())
        {
            ret = tmp;
            break;
        }
    }
    return ret;
};
std::array<int, 6> isPairs(int nums[15])
{
    std::array<int, 6> ret{};
    std::array<std::pair<int, int>, 7> pairs;
    int i = 0;
    for (int n = A; n >= 2; n--)
    {
        if (nums[n])
            pairs[i++] = {n, nums[n]};
    }

    sort(pairs.begin(), pairs.begin() + i,
         [](const auto &lhs, const auto &rhs) -> bool
         {
             if (lhs.second == rhs.second)
                 return lhs.first > rhs.first;
             return lhs.second > rhs.second;
         });

    int append;
    switch (pairs[0].second)
    {
    case 1:
        ret[0] = HIGHCARD;
        append = 5;
        break;
    case 2:
        sort(pairs.begin() + 2, pairs.begin() + 4, std::greater<>());
        if (pairs[1].second == 2)
        {
            ret[0] = TWOPAIRS;
            append = 3;
        }
        else
        {
            ret[0] = ONEPAIR;
            append = 4;
        }
        break;
    case 3:
        if (pairs[1].second > 1)
        {
            ret[0] = FULLHOUSE;
            append = 2;
        }
        else
        {
            ret[0] = THREEOFAKIND;
            append = 3;
        }
        break;
    case 4:
        ret[0] = FOUROFAKIND;
        append = 2;
        break;
    }

    for (int i = 0; i < append; i++)
        ret[i + 1] = pairs[i].first;

    return ret;
};
