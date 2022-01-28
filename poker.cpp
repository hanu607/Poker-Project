#include "table.h"

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
    return {s, n};
}

void test()
{
    Table T;
    Player shin(T);
    Player father(T);
    // T.append_player(shin);
    // T.append_player(father);
    cout << "P1: Shin Jun Yeop" << endl;
    shin.append_hand(parseCard());
    shin.append_hand(parseCard());
    cout << "P2: Shin's Father" << endl;
    father.append_hand(parseCard());
    father.append_hand(parseCard());
    cout << "Board" << endl;
    T.append_board(parseCard());
    T.append_board(parseCard());
    T.append_board(parseCard());
    T.append_board(parseCard());
    T.append_board(parseCard());

    bool res = T.Showdown();
    if (res) cout << "Shin Wins!!!" << '\n';
    else cout << "Father Wins!!!" << '\n';
    auto shinrank = T.computeRank(shin);
    auto fatherrank = T.computeRank(father);
    cout << "Shin: " << shinrank.first << ' ' << shinrank.second.first << ' ' << shinrank.second.second << '\n';
    cout << "Father: " << fatherrank.first << ' ' << fatherrank.second.first << ' ' << fatherrank.second.second << '\n';
}

int main()
{
    test();
}
