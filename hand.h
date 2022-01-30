#ifndef HAND_H
#define HAND_H
#include <set>
#include <deque>

struct cmp
{
    bool operator()(const std::pair<int, int> &lhs, const std::pair<int, int> &rhs) const
    {
        if (lhs.second == rhs.second)
            return lhs.first > rhs.first;
        return lhs.second > rhs.second;
    }
};

class Hand
{
private:
    int nums[15];
    int suits[4];
    std::set<std::pair<int, int>, cmp> hands;

public:
    Hand() : nums{}, suits{} {}

    void insert(const std::pair<int, int> &card);
    std::pair<int, std::pair<int, int>> isStraight() const;
    std::pair<int, std::pair<int, int>> isStraight(const int &s) const;
    std::pair<int, std::pair<int, int>> isFlush() const;
    std::pair<int, std::pair<int, int>> isPairs() const;
};

#endif
