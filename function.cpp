#include "enum.h"
#include "function.h"
#include "table.h"
#include <algorithm>
#include <deque>

std::array<int, 6> isStraight(int nums[15])
{
    std::array<int, 6> ret{};
    std::deque<int> dq;
    for (int n = A; n > 0; n--)
    {   
        if (!nums[n]) continue;
        if (!dq.empty() && dq.back() - 1 != n)
            dq.clear();
        dq.push_back(n);
        if (dq.size() == 5)
        {
            ret[0] = STRAIGHT;
            ret[1] = dq.front();
            break;
        }
    }
    return ret;
};
std::array<int, 6> isStraightFlush(std::array<std::pair<int, int>, 8> &hand, const int &s)
{
    std::array<int, 6> ret{};
    std::deque<int> dq;
    for (const auto &card : hand)
    {
        if (card.first != s)
            continue;
        if (card.second == A)
            hand[7] = {s, 1};
        if (!dq.empty() && dq.back() - 1 != card.second)
            dq.clear();
        dq.push_back(card.second);
        if (dq.size() == 5)
        {
            ret[0] = STRAIGHTFLUSH;
            ret[1] = dq.front();
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
    sort(arr.begin() + 2, arr.end(), std::greater<>());

    int append = 0;
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
        ret[i + 1] = (arr[i].first);

    return ret;
};

int *Bruteforce(Table &T)
{
    bfSuit(T, T.cur_size);
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

        /*
        T.computeRank(T.players[1]);
        if (T.Showdown() == -1) {
            for (const auto &card : T.community)
                printf("(%d, %d) ", card.first, card.second);
            std::cout << '\n';
        }
        */
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
