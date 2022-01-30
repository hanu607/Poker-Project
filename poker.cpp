#include "table.h"
#include "player.h"
#include "enum.h"
#include "hand.h"
using namespace std;









void test()
{
    Table T;
    Player shin(T);
    Player father(T);
    cout << "P1: Shin Jun Yeop" << endl;
    shin.insertStarting(parseCard());
    shin.insertStarting(parseCard());
    cout << "P2: Shin's Father" << endl;
    father.insertStarting(parseCard());
    father.insertStarting(parseCard());
    cout << "Board" << endl;
    T.insertCommunity(parseCard());
    T.insertCommunity(parseCard());
    T.insertCommunity(parseCard());
    T.insertCommunity(parseCard());
    T.insertCommunity(parseCard());

    bool res = T.Showdown();
    if (res)
        cout << "Shin Wins!!!" << '\n';
    else
        cout << "Father Wins!!!" << '\n';
    auto shinrank = shin.computeRank();
    auto fatherrank = father.computeRank();
    cout << "Shin: " << shinrank.first << ' ' << shinrank.second.first << ' ' << shinrank.second.second << '\n';
    cout << "Father: " << fatherrank.first << ' ' << fatherrank.second.first << ' ' << fatherrank.second.second << '\n';
}

int main()
{
    test();
}








