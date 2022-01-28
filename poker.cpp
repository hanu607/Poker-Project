#include <iostream>
#include <deque>
#include <vector>
#include <set>
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
struct cmp
{
    bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs) const
    {
        return lhs.second > rhs.second;
    }
};
class Player
{
private:
    int id;
    int nums[15];
    int suits[4];
    set<pair<int, int>, cmp> hands;

public:
    Player() : id(++idcnt), nums{}, suits{} { }

    void append_hand(const pair<int, int> &card)
    {
        hands.insert(card);
        auto [s, n] = card;
        this->nums[n]++;
        this->suits[s]++;
        if (n == A)
            nums[1]++;
    };
    static int idcnt;

    friend class Table;
};

int Player::idcnt = 0;

class Table
{
private:
    vector<Player*> players;
    vector<pair<int, int>> board;

public:
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

    void append_board(const pair<int, int> &card)
    {
        board.push_back(card);
        for (Player* it : players)
            (*it).append_hand(card);
    }

    void append_player(Player &p)
    {   
        players.push_back(&p);
    }

    pair<int, pair<int, int>> isStraight(Player &p) const
    {
        pair<int, pair<int, int>> rank = {0, {0, 0}};
        deque<int> dq;
        for (auto it : p.hands)
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
    pair<int, pair<int, int>> isStraight(Player &p, int s) const
    {
        pair<int, pair<int, int>> rank = {0, {0, 0}};
        deque<pair<int, int>> dq;
        for (auto it : p.hands)
        {   
            if (it.first != s) continue;
            if (dq.empty() || dq.back().second - 1 == it.second)
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
    pair<int, pair<int, int>> isFlush(Player &p) const
    {
        pair<int, pair<int, int>> rank = {0, {0, 0}};
        for (int s = SPADE; s <= DIAMOND; s++)
        {
            if (p.suits[s] < 5)
                continue;
            rank.first = FLUSH;
            for (auto it : p.hands)
                if (it.first == s)
                {
                    rank.second.first = it.second;
                    break;
                }

            int high = isStraight(p, s).second.first;
            if (high == 0)
                break;
            rank.first = STRAIGHTFLUSH;
            rank.second.first = high;
        }
        return rank;
    }
    pair<int, pair<int, int>> isPairs(Player &p) const
    {
        int mx = 0;
        pair<int, pair<int, int>> rank = {0, {0, 0}};
        for (int n = A; n > 1; n--)
        {
            if (p.nums[n] == 4)
                return {FOURCARD, {n, 0}};
            else if (p.nums[n] == 3)
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
            else if (p.nums[n] == 2)
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
            else if (p.nums[n] == 1)
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
    pair<int, pair<int, int>> computeRank(Player &p) const
    {
        auto Flush = isFlush(p);
        if (Flush.first)
            return Flush;
        else
        {
            auto Straight = isStraight(p);
            if (Straight.first)
                return Straight;
            else
                return isPairs(p);
        }
    }

    bool Showdown()
    {
        return this->computeRank(*players[0]) > this->computeRank(*players[1]);
    }
};

pair<int, int> parseCard();

void test()
{
    Table T;
    Player shin;
    Player father;
    T.append_player(shin);
    T.append_player(father);
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
