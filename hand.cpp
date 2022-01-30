#include "hand.h"
#include "enum.h"



pair<int, int> parseCard()
{
    char i, j;
    int n, s;
    while (cin >> i >> j)
    {
        // input number
        if ('2' <= i && i <= '9')
            n = i - '0';
        else if (i == 'T')
            n = T;
        else if (i == 'J')
            n = J;
        else if (i == 'Q')
            n = Q;
        else if (i == 'K')
            n = K;
        else if (i == 'A')
            n = A;
        else
            continue;
        // input suit
        if (j == 's')
            s = SPADE;
        else if (j == 'h')
            s = HEART;
        else if (j == 'c')
            s = CLUB;
        else if (j == 'd')
            s = DIAMOND;
        else
            continue;
        // return {suit, number}
        break;
    }
    return { s, n };
}

void Hand::insert(const pair<int, int>& card)
{
    hands.insert(card);
    int s = card.first;
    int n = card.second;
    
    nums[n]++;
    suits[s]++;
    if (n == A)
        nums[1]++;
}
pair<int, pair<int, int>> Hand::isStraight() const
{
    pair<int, pair<int, int>> rank = { 0, {0, 0} };
    deque<int> dq(5);
    for (int n = A; n > 0; n--)
    {
        if (!nums[n])
            continue;
        if (!dq.empty() && dq.back() - 1 != n)
            dq.clear();
        dq.push_back(n);
        if (dq.size() == 5)
        {
            rank.first = STRAIGHT;
            rank.second.first = dq.front();
            break;
        }
    }
    return rank;
}
pair<int, pair<int, int>> Hand::isStraight(const int& s) const
{
    pair<int, pair<int, int>> rank = { 0, {0, 0} };
    set<pair<int, int>, cmp> temp(hands);
    deque<pair<int, int>> dq(5);
    for (auto it : temp)
    {
        if (it.first != s)
            continue;
        if (it.second == A)
            temp.insert({ s, 1 });
        if (!dq.empty() && dq.back().second - 1 != it.second)
            dq.clear();
        dq.push_back(it);
        if (dq.size() == 5)
        {
            rank.first = STRAIGHT;
            rank.second.first = dq.front().second;
            break;
        }
    }
    temp.erase({ s, 1 });
    return rank;
}
pair<int, pair<int, int>> Hand::isFlush() const
{
    pair<int, pair<int, int>> rank = { 0, {0, 0} };
    for (int s = SPADE; s <= DIAMOND; s++)
    {
        if (suits[s] < 5)
            continue;
        rank.first = FLUSH;
        for (auto it : hands)
            if (it.first == s)
            {
                rank.second.first = it.second;
                break;
            }

        int high = isStraight(s).second.first;
        if (high == 0)
            break;
        rank.first = STRAIGHTFLUSH;
        rank.second.first = high;
    }
    return rank;
}
pair<int, pair<int, int>> Hand::isPairs() const
{
    int mx = 0;
    pair<int, pair<int, int>> rank = { 0, {0, 0} };
    for (int n = A; n > 1; n--)
    {
        if (nums[n] == 4)
            return { FOUROFAKIND, {n, 0} };
        else if (nums[n] == 3)
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
                rank.first = THREEOFAKIND;
                rank.second.first = n;
                mx = 3;
            }
        }
        else if (nums[n] == 2)
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
        else if (nums[n] == 1)
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

