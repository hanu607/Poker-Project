#ifndef FUNCTION_H
#define FUNCTION_H
#include <array>

std::array<int, 6> isStraight(std::array<std::pair<int, int>, 8> &hand);
std::array<int, 6> isStraightFlush(std::array<std::pair<int, int>, 8> &hand, const int &s);
std::array<int, 6> isFlush(std::array<std::pair<int, int>, 8> &hand, int suits[4]);
std::array<int, 6> isPairs(int nums[15]);

#endif
