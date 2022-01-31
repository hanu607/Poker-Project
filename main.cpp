#include "enum.h"
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
    shin.insertHand(parseCard());
    shin.insertHand(parseCard());
    std::cout << "P2: Shin's Father" << '\n';
    father.insertHand(parseCard());
    father.insertHand(parseCard());
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
    auto shinrank = T.computeRank(shin.getHand());
    auto fatherrank = T.computeRank(father.getHand());
    for (auto e : shinrank)
        std::cout << e << ' ';
    std::cout << '\n';
    for (auto e : fatherrank)
        std::cout << e << ' ';
}

int main()
{
    test();
}
