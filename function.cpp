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
std::array<int, 6> isStraightFlush(std::array<std::pair<int, int>, 8> &hand, const int &s)
{
    std::array<int, 6> ret{};

    int head = 0, tail = 0;
    for (const auto &card : hand)
    {
        tail++;
        if (card.first != s)
            head = tail;
        else
        {
            if (card.second == A)
                hand[7] = {s, 1};
            if (head != tail && hand[tail - 1].second - 1 != hand[tail].second)
                head = tail - 1;
        }
        if (tail - head == 5)
        {
            ret[0] = STRAIGHTFLUSH;
            ret[1] = hand[head].second;
            break;
        }
    }
    hand[7] = {-1, 0};
    return ret;
};
std::array<int, 6> isFlush(std::array<std::pair<int, int>, 8> &hand, int suits[4])
{
    std::array<int, 6> ret{};
    for (int s = SPADE; s <= DIAMOND; s++)
    {
        if (suits[s] < 5)
            continue;
        ret[0] = FLUSH;
        {
            int pos = 1;
            for (const auto &card : hand)
                if (card.first == s)
                    ret[pos++] = card.second;
            if (pos > 5)
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
std::array<int, 6> isPairs(int nums[15])
{
    std::array<int, 6> ret{};
    std::array<std::pair<int, int>, 7> arr;
    int idx = 0;
    for (int n = A; n >= 2; n--)
    {
        if (nums[n])
            arr[idx++] = {n, nums[n]};
    }

    sort(arr.begin(), arr.begin() + idx,
         [](const auto &lhs, const auto &rhs) -> bool
         {
             if (lhs.second == rhs.second)
                 return lhs.first > rhs.first;
             return lhs.second > rhs.second;
         });
    sort(arr.begin() + 2, arr.begin() + 4, std::greater<>());

    int append;
    switch (arr[0].second)
    {
    case 1:
        ret[0] = HIGHCARD;
        append = 5;
        break;
    case 2:
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
        break;
    case 3:
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
        break;
    case 4:
        ret[0] = FOUROFAKIND;
        append = 2;
        break;
    }

    for (int i = 0; i < append; i++)
        ret[i + 1] = arr[i].first;

    return ret;
};

int *bruteforce(Table &T)
{
    backtracking(T, T.cur_size);
    return T.res;
}
void backtracking(Table &T, const int &k)
{
    if (k == 5)
    {
        T.res[T.Showdown() + 1]++;
        return;
    }

    int s_start = k > T.cur_size ? T.community[k - 1].first : 0;
    for (int s = s_start; s <= DIAMOND; s++)
    {
        int n_start = (k > T.cur_size && T.community[k - 1].first == s) ? T.community[k - 1].second - 1 : A;
        for (int n = n_start; n >= 2; n--)
        {
            if (T.deck[s][n])
                continue;
            T.community[k] = {s, n};
            backtracking(T, k + 1);
        }
    }
}
