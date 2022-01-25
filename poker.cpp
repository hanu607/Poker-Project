#include <iostream>
#include <vector>
#include <deque>
#define number first
#define suit second

using namespace std;

enum Broadway {
    T = 10, J, Q, K, A
};
enum Suits {
    SPADE, HEART, CLUB, DIAMOND
};
enum Score {
    HighCard = 0, OnePair = 100, TwoPair = 200, Tripple = 300, Straight = 400, Flush = 500, FullHouse = 600, FourCard = 700, StraightFlush = 900
};

pair<int, int> getCard()
{
    char i, j;
    pair<int, int> card;
    while (cin >> i >> j)
    {
        //input number
        if ('2' <= i && i <= '9')
            card.number = i - '0';
        else if (i == 'T')
            card.number = T;
        else if (i == 'J')
            card.number = J;
        else if (i == 'Q')
            card.number = Q;
        else if (i == 'K')
            card.number = K;
        else if (i == 'A')
            card.number = A;
        else
            continue;
        //input suit
        if (j == 's')
            card.suit = SPADE;
        else if (j == 'h')
            card.suit = HEART;
        else if (j == 'c')
            card.suit = CLUB;
        else if (j == 'd')
            card.suit = DIAMOND;
        else
            continue;
        //return <number, suit>
        return card;
    }
}

int cards[4][15];
int nums[15];
int suits[4];

namespace Rank {
    
    
    int isStraight(int s) {
        int* ptr = nums;
        if (s != -1) ptr = cards[s];
        int res = 0;
        deque<int> dq;
        for (int n = A; n > 0; n--) {
            if (!ptr[n]) dq.clear();
            else if (dq.empty() || dq.back()-1 == n) dq.push_back(n);
            if (dq.size() == 5) {
                res += Straight + dq.front();
                break;
            }
        }
        return res;
    }

    int isFlush() {
        int res = 0;
        for (int s = SPADE; s <= DIAMOND; s++) {
            if (suits[s] < 5) continue;
            res += Flush;
            res += isStraight(s);
            if (res > StraightFlush) break;
            for (int n = A; n > 1; n--) {
                if (cards[s][n]) {
                    res += n;
                    return res;
                }
            }
        }
        return res;
    }
};

void test() {
    cout << Rank::isFlush() << '\n';
    cout << Rank::isStraight(-1) << '\n';
}

int main()
{
    for (int i = 0; i < 7; i++)
    {
        auto [n, s] = getCard();
        cards[s][n] = 1;
        nums[n]++;
        suits[s]++;
        if (n == A) {
            cards[s][1] = 1;
            nums[1]++;
        }
    }
    test();
}
