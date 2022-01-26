#include <iostream>
#include <deque>
// #include <vector>
#include <algorithm>

using namespace std;

enum Broadway
{
    T = 10,
    J,
    Q,
    K,
    A
};
enum Suits
{
    SPADE,
    HEART,
    CLUB,
    DIAMOND
};
enum Ranks
{
    HIGHCARD,
    ONEPAIR,
    TWOPAIR,
    TRIPPLE,
    STRAIGHT,
    FLUSH,
    FULLHOUSE,
    FOURCARD,
    STRAIGHTFLUSH
};

int cards[4][15];
int nums[15];
int suits[4];

pair<int, int> setCard()
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
        return {s, n};
    }
}

namespace Rank
{
    pair<int, int> isStraight(int s)
    {
        int *arr = (s == -1 ? nums : cards[s]);
        pair<int, int> rank = {0, 0};
        deque<int> dq;
        for (int n = A; n > 0; n--)
        {
            if (!arr[n])
                dq.clear();
            else if (dq.empty() || dq.back() - 1 == n)
                dq.push_back(n);
            if (dq.size() == 5)
            {
                rank.first = STRAIGHT;
                rank.second = dq.front();
                break;
            }
        }
        return rank;
    }

    pair<int, int> isFlush()
    {
        pair<int, int> rank = {0, 0};
        for (int s = SPADE; s <= DIAMOND; s++)
        {
            if (suits[s] < 5)
                continue;
            rank.first = FLUSH;
            for (int n = A; n > 1; n--)
                if (cards[s][n])
                {
                    rank.second = n;
                    break;
                }

            int high = isStraight(s).second;
            if (high == 0)
                break;
            rank.first = STRAIGHTFLUSH;
            rank.second = high;
        }
        return rank;
    }

    pair<int, pair<int, int>> isPair()
    {
        int mx = 0;
        pair<int, pair<int, int>> rank = {0, {0, 0}};
        for (int n = A; n > 1; n--)
        {
            if (nums[n] == 4)
                return {FOURCARD, {n, 0}};
            else if (nums[n] == 3)
            {
                if (mx == 3)
                {
                    rank.first = FULLHOUSE;
                    rank.second.second = n;
                    break;
                }
                else if (mx == 2)
                {
                    rank.first = FULLHOUSE;
                    rank.second.second = rank.second.first;
                    rank.second.first = n;
                    break;
                }
                else
                {
                    rank.first = TRIPPLE;
                    rank.second.first = n;
                    mx = 3;
                }
            }
            else if (nums[n] == 2)
            {
                if (mx == 3)
                {
                    rank.first = FULLHOUSE;
                    rank.second.second = n;
                    break;
                }
                if (mx == 2)
                {
                    rank.first = TWOPAIR;
                    if (rank.second.second == 0)
                        rank.second.second = n;
                    else
                        break;
                }
                else
                {
                    rank.first = ONEPAIR;
                    rank.second.first = n;
                    mx = 2;
                }
            }
            else if (nums[n] == 1)
            {
                if (mx == 0)
                {
                    rank.first = HIGHCARD;
                    rank.second.first = n;
                    mx = 1;
                }
            }
        }
        return rank;
    }
};

void bruteforce()
{
    bool nums[52];
    fill(nums, nums + 5, false);
    fill(nums + 5, nums + 52, true);
    unsigned long long ans = 0;

    do
    {
        // for (int i = 0; i < 52; i++) {
        //     if (!nums[i]) cout << i + 2 << ' ';
        // }
        // cout << '\n';
    } while (next_permutation(nums, nums + 52));

    cout << ans;
}

void test()
{
    for (int i = 0; i < 7; i++)
    {
        auto [s, n] = setCard();
        cards[s][n] = 1;
        nums[n]++;
        suits[s]++;
        if (n == A)
        {
            cards[s][1] = 1;
            nums[1]++;
        }
    }
    auto t1 = Rank::isFlush();
    auto t2 = Rank::isStraight(-1);
    auto t3 = Rank::isPair();
    cout << t1.first << ' ' << t1.second << '\n';
    cout << t2.first << ' ' << t2.second << '\n';
    cout << t3.first << ' ' << t3.second.first << ' ' << t3.second.second << '\n';
}

int main()
{
    test();
    // bruteforce();
}
