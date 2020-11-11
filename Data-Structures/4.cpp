#include<iostream>
#include<cmath>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;

typedef pair<int, int> Position;

const int MAX_X = 100, MAX_Y = 100;
bool lawful(int x, int y)
{
    return x <= 100 && y <= 100 && x >= -100 && y >= -100;
}
const int SUCC = 8;
const int SUCC_X[] = { 1,1,2,2,-1,-1,-2,-2 };
const int SUCC_Y[] = { 2,-2,1,-1,2,-2,1,-1 };
Position dest;

class Map
{
private:
    bool _map[2 * MAX_X + 1][2 * MAX_Y + 1];
    Position _trans(Position pos)
    {
        return make_pair(pos.first + MAX_X, pos.second + MAX_Y);
    }
public:
    Map()
    {
        memset(_map, 1, sizeof(_map));
    }
    void setDeny(Position pos)
    {
        auto tmp = _trans(pos);
        _map[tmp.first][tmp.second] = false;
    }
    bool check(Position pos)
    {
        auto tmp = _trans(pos);
        return _map[tmp.first][tmp.second];
    }
} map;

class State
{
private:
    Position _pos;
    int _move;
    int _expect = -1;
    int _getExpect()const
    {
        return _move + (abs(_pos.first - dest.first) + abs(_pos.second - dest.second)) / 3;
    }
public:
    State(Position pos = make_pair(0, 0), int move = 0, int expect = -1) : _pos(pos), _move(move)
    {
        _expect = _getExpect();
    }
    void setMove(int move)
    {
        _move = move;
    }
    int getMove()const
    {
        return _move;
    }
    vector<State> getSucc()const
    {
        vector<State> ans;
        for (int i = 0; i != SUCC; i++)
        {
            if (lawful(_pos.first + SUCC_X[i], _pos.second + SUCC_Y[i]))
            {
                auto tmp = make_pair(_pos.first + SUCC_X[i], _pos.second + SUCC_Y[i]);
                if (map.check(tmp)) ans.push_back(State(tmp, _move + 1));
            }
        }
        return ans;
    }
    int getExpect()const
    {
        if (_expect == -1) throw(-1);
        return _expect;
    }
    Position getPos()const
    {
        return _pos;
    }
    bool operator>(const State s)const
    {
        return getExpect() < s.getExpect(); //鍙嶅悜鐨勫師鍥犳槸, std浼樺厛闃熷垪榛樿澶ф牴鍫?
    }
    bool operator<(const State s)const
    {
        return s > (*this);
    }
};

priority_queue<State> que;

int run()
{
    if (que.empty()) return -1;
    auto tmp = que.top();
    que.pop();
    auto succ = tmp.getSucc();
    for (auto i : succ)
    {
        auto pos = i.getPos();
        if (pos.first == dest.first && pos.second == dest.second) return i.getMove();
        map.setDeny(pos);
        que.push(i);
    }
    return 0;
}

int main()
{
    cin >> dest.first >> dest.second;
    int n;
    cin >> n;
    for (int i = 0; i != n; i++)
    {
        int x, y;
        cin >> x >> y;
        map.setDeny(make_pair(x, y));
    }
    if (dest.first == 0 && dest.second == 0) return 0;
    map.setDeny(make_pair(0, 0));
    que.push(State(make_pair(0, 0), 0));
    while (true)
    {
        int ans = run();
        if (ans == -1)
        {
            cout << "fail";
            return 0;
        }
        else if (ans != 0)
        {
            cout << ans;
            return 0;
        }
    }
    return 0;
}