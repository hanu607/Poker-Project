#include <iostream>

using namespace std;
char broadway[5] = {'T', 'J', 'Q', 'K', 'A'};

pair<int, int> GetCard()
{
    char i, j;
    pair<int, int> card;
    while (cin >> i >> j)
    {
        //input Number
        if ('2' <= i && i <= '9')
            card.first = i - '0';
        else if (i == 'T')
            card.first = 10;
        else if (i == 'J')
            card.first = 11;
        else if (i == 'Q')
            card.first = 12;
        else if (i == 'K')
            card.first = 13;
        else if (i == 'A')
            card.first = 14;
        else
            continue;
        //input Shape
        if (j == 's')
            card.second = 0;
        else if (j == 'h')
            card.second = 1;
        else if (j == 'c')
            card.second = 2;
        else if (j == 'd')
            card.second = 3;
        else
            continue;
        //return <Number,Shape>
        return card;
    }
}
int main()
{
    while (1)
    {
        auto temp = GetCard();
        cout << temp.first << " " << temp.second << endl;
    }
    return 0;
}