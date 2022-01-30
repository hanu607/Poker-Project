#ifndef HAND_H
#define HAND_H
#include<set>
#include<iostream>
#include<deque>


using namespace std;
class Table;
struct cmp
{
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) const
    {
        if (lhs.second == rhs.second)
            return lhs.first > rhs.first;
        return lhs.second > rhs.second;
    }
};

pair<int, int> parseCard();

class Hand
{
private:
    int nums[15];
    int suits[4];
    set<pair<int, int>, cmp> hands;

public:
    Hand() : nums{}, suits{} {}

    void insert(const pair<int, int>& card);
    pair<int, pair<int, int>> isStraight() const;
    pair<int, pair<int, int>> isStraight(const int& s) const;
    pair<int, pair<int, int>> isFlush() const;
    pair<int, pair<int, int>> isPairs() const;
};

#endif