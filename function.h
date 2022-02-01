#ifndef FUNCTION_H
#define FUNCTION_H
#include <vector>

std::vector<int> isStraight(std::vector<std::pair<int, int>>& hand);
std::vector<int> isStraightFlush(std::vector<std::pair<int, int>>& hand, const int &s);
std::vector<int> isFlush(std::vector<std::pair<int, int>>& hand, int suits[]);
std::vector<int> isPairs(int nums[]);

#endif
