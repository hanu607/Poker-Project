#include "enum.h"
#include "hand.h"
#include "player.h"
#include "table.h"
#include <iostream>

std::pair<int, int> parseCard()
{
    char i, j;
    int n, s;
    while (std::cin >> i >> j)
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
    return {s, n};
}

void test()
{
    Table T;
    Player shin(T);
    Player father(T);
    std::cout << "P1: Shin Jun Yeop" << '\n';
    shin.insertStarting(parseCard());
    shin.insertStarting(parseCard());
    std::cout << "P2: Shin's Father" << '\n';
    father.insertStarting(parseCard());
    father.insertStarting(parseCard());
    std::cout << "Board" << '\n';
    T.insertCommunity(parseCard());
    T.insertCommunity(parseCard());
    T.insertCommunity(parseCard());
    T.insertCommunity(parseCard());
    T.insertCommunity(parseCard());

    bool res = T.Showdown();
    if (res)
        std::cout << "Shin Wins!!!" << '\n';
    else
        std::cout << "Father Wins!!!" << '\n';
    auto shinrank = shin.computeRank();
    auto fatherrank = father.computeRank();
    std::cout << "Shin: " << shinrank.first << ' ' << shinrank.second.first << ' ' << shinrank.second.second << '\n';
    std::cout << "Father: " << fatherrank.first << ' ' << fatherrank.second.first << ' ' << fatherrank.second.second << '\n';
}

int main()
{
    test();
}
