#include "enum.h"
#include "player.h"
#include "table.h"
#include <iostream>
#include <time.h>

std::pair<int, int> parseCard()
{
    char i, j;
    int n, s;
    while (std::cin >> i >> j)
    {
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
        break;
    }
    return {s, n};
}

int main()
{   
    Table T;
    std::cout << "Hero: ";
    T.insertStarting(0, parseCard());
    T.insertStarting(0, parseCard());
    std::cout << "Villain: ";
    T.insertStarting(1, parseCard());
    T.insertStarting(1, parseCard());
    std::cout << "Board: ";
    int n;
    std::cin >> n;
    while (n--)
        T.insertCommunity(parseCard());

    clock_t start, end;
    start = clock();
    T.bruteforce();
    end = clock();
    double t = (double)(end - start);
    printf("%fs elapsed.\n", t / 1000);

    for (int i = 0; i < 2; i++)
    {
        const auto &temp = T.getResult(i);
        printf("(%f %%, %f %%)\n", temp.first * 100, temp.second * 100);
    }
}

/*
TO DO:

Major:
Implement the user prompt.
Make the program robust.

More:
Modify program to work with more than 2 players.
Modify bruteforce to work with a player without hand.

Options:
Convert enums to enum classes.
Comment whole codes.
*/
