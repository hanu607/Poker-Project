#ifndef FUNCTION_H
#define FUNCTION_H
#include <array>

std::array<int, 6> isStraight(int nums[15]);
std::array<int, 6> isStraightFlush(int deck[4][15], const int &s);
std::array<int, 6> isFlush(bool deck[4][15], int suits[4]);
std::array<int, 6> isPairs(int nums[15]);

#endif
