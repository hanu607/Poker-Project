#include <iostream>
#include <vector>
using namespace std;

pair<int, int> board[5];
vector<pair<int, int>> v;
bool deck[4][15];
int limit = 5;
int ans = 0;

void func2(int k)
{
    if (k == limit)
    {
        for (int i = 0; i < limit; i++)
            printf("(%d, %d) ", board[i].first, board[i].second);
        cout << '\n';
        ans++;
        return;
    }
    int st = k && board[k-1].first == board[k].first ? board[k-1].second + 1 : 2;
    for (int n = st; n <= 14; n++)
    {   
        if (deck[board[k].first][n]) continue;
        board[k].second = n;
        func2(k + 1);
    }
}

void func1(int k)
{
    if (k == limit)
    {   
        func2(0);
        return;
    }
    int st = k ? board[k - 1].first : 0;
    for (int s = st; s <= 3; s++)
    {
        board[k].first = s;
        func1(k + 1);
    }
}

int main()
{   
    v.push_back({0, 3});
    v.push_back({2, 2});
    v.push_back({4, 11});
    // v.push_back({0, 10});
    deck[0][3] = true;
    deck[2][2] = true;
    deck[3][11] = true;
    // deck[0][10] = true;
    limit = 5 - v.size();
    func1(0);
    cout << ans;
}
