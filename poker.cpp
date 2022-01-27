#include <iostream>
#include <deque>
#include <vector>
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
bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.second > b.second;
}

vector<pair<int, int>> board;

class Player
{
private:
    int id;
    // static int deck[4][15];
    int nums[15];
    int suits[4];
    vector<pair<int, int>> hands;

public:
    Player() : id(++idcnt)
    {
        fill(nums, nums + 15, 0);
        fill(suits, suits + 4, 0);
    }
    void setCard(const pair<int, int> &);
    void inputCard(int);
    void prepare();
    pair<int, pair<int, int>> computeRank();
    static int idcnt;
};

pair<int, int> parseCard();

bool Showdown(Player &p1, Player &p2);

void test()
{
    Player shin;
    Player father;
    cout << "P1: Shin Jun Yeop" << endl;
    shin.inputCard(2);
    cout << "P2: Shin's God Father" << endl;
    father.inputCard(2);
    cout << "Board" << endl;
    board.push_back(parseCard());
    board.push_back(parseCard());
    board.push_back(parseCard());
    board.push_back(parseCard());
    board.push_back(parseCard());

    // bool res = Showdown(shin, father);
    auto shinrank = shin.computeRank();
    auto fatherrank = father.computeRank();
    // if (res) cout << "Shin Wins!!!" << '\n';
    // else cout << "Father Wins!!!" << '\n';
    cout << "Shin: " << shinrank.first << ' ' << shinrank.second.first << ' ' << shinrank.second.second << '\n';
    cout << "Father: " << fatherrank.first << ' ' << fatherrank.second.first << ' ' << fatherrank.second.second << '\n';
}

int main()
{
    test();
}

namespace Rank
{
    pair<int, pair<int, int>> isStraight(const vector<pair<int, int>> &hands)
    {
        pair<int, pair<int, int>> rank = {0, {0, 0}};
        deque<int> dq;
        for (auto it : hands)
        {
            if (dq.empty() || dq.back() - 1 == it.second)
                dq.push_back(it.second);
            else
                dq.clear();
            if (dq.size() == 5)
            {
                rank.first = STRAIGHT;
                rank.second.first = dq.front();
                break;
            }
        }
        return rank;
    }

    pair<int, pair<int, int>> isStraight(const vector<pair<int, int>> &hands, int s)
    {
        pair<int, pair<int, int>> rank = {0, {0, 0}};
        deque<pair<int, int>> dq;
        for (auto it : hands)
        {
            if (dq.empty() || dq.back().second - 1 == it.second && dq.back().first == it.first)
                dq.push_back(it);
            else
                dq.clear();
            if (dq.size() == 5)
            {
                rank.first = STRAIGHT;
                rank.second.first = dq.front().first;
                break;
            }
        }
        return rank;
    }

    pair<int, pair<int, int>> isFlush(int *suits, const vector<pair<int, int>> &hands)
    {
        pair<int, pair<int, int>> rank = {0, {0, 0}};
        for (int s = SPADE; s <= DIAMOND; s++)
        {
            if (suits[s] < 5)
                continue;
            rank.first = FLUSH;
            for (auto it : hands)
                if (it.first == s)
                {
                    rank.second.first = it.second;
                    break;
                }

            int high = isStraight(hands, s).second.first;
            if (high == 0)
                break;
            rank.first = STRAIGHTFLUSH;
            rank.second.first = high;
        }
        return rank;
    }

    pair<int, pair<int, int>> isPairs(int* nums)
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

void Player::setCard(const pair<int, int> &card)
{
    hands.push_back(card);
}

void Player::inputCard(int n)
{
    while (n--)
        setCard(parseCard());
}

void Player::prepare()
{
    for (auto it : board)
        setCard(it);
    for (auto it : hands)
    {
        auto [s, n] = it;
        // deck[s][n] = id;
        nums[n]++;
        suits[s]++;
        if (n == A)
        {
            // deck[s][1] = id;
            nums[1]++;
        }
    }
    sort(hands.begin(), hands.end(), cmp);
}

pair<int, pair<int, int>> Player::computeRank()
{
    prepare();
    auto Flush = Rank::isFlush(suits, hands);
    if (Flush.first)
    {
        return Flush;
    }
    else
    {
        auto Straight = Rank::isStraight(hands);
        if (Straight.first)
        {
            return Straight;
        }
        else
        {
            auto Pairs = Rank::isPairs(nums);
            return Pairs;
        }
    }
}

bool Showdown(Player &p1, Player &p2)
{
    return p1.computeRank() > p2.computeRank();
}

int Player::idcnt = 0;

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
