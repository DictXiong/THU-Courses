#include<cstdio>
#include<vector>
#include<queue>
#include<list>

#define likely(x) __builtin_expect(!!(x), 1) // x is likely to be true       
#define unlikely(x) __builtin_expect(!!(x), 0) // x is likely to be false

#define test

using namespace std;

template<class T>void read(T& x)
{
    x = 0; int f = 0; char ch = getchar();
    while (ch < '0' || ch>'9') { f |= (ch == '-'); ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    x = f ? -x : x;
    return;
}

enum class Status
{
    SON = -1, NONE = 0, FATHER = 1, UNDEF, SEARCHING
};

class Query
{
public:
    short first, second;
    Status ans;
    Query(const short& a, const short& b, Status c=Status::UNDEF) : first(a), second(b), ans(c) {}

    inline bool finished()
    {
        return (ans != Status::UNDEF && ans != Status::SEARCHING);
    }
    void check(short a)
    {
        if (a == first) ans = Status::SON;
        else if (a == second) ans = Status::FATHER;
        else throw(12);
    }
};

class Poster
{
public:
    short who, queryNum;
    Poster(const short& a, const short& b) : who(a), queryNum(b) {};
};

const int N = 500;
int n, m, k;
int indegree[N];
vector<short> adj[N];
vector<Query> queries;
vector<Poster> posters[N];

bool AOL()
{
    int pointsLeft = n;
    queue<short> que;

    for (int i = 0; i != n; i++)
    {
        if (indegree[i] == 0)
        {
            que.emplace(i);
        }
    }

    while (!que.empty())
    {
        auto now = que.front();
        que.pop();
        pointsLeft--;
        vector<Poster> passPosters;
        for (auto& i : posters[now])
        {
            if (i.who == now)
            {
                queries[i.queryNum].check(i.who);
            }
            else if (!queries[i.queryNum].finished())
                passPosters.push_back(move(i));
        }
        for (int i = 0; i != k; i++)
        {
            if (queries[i].finished()) continue;
            if (queries[i].first == now)
            {
                if (queries[i].ans != Status::SEARCHING)
                {
                    queries[i].ans = Status::SEARCHING;
                    passPosters.emplace_back(queries[i].second, i);
                }
                else queries[i].ans = Status::NONE;
            }
            else if (queries[i].second == now)
            {
                if (queries[i].ans != Status::SEARCHING)
                {
                    passPosters.emplace_back(queries[i].first, i);
                    queries[i].ans = Status::SEARCHING;
                }
                else queries[i].ans = Status::NONE;
            }
        }
        for (auto& i : adj[now])
        {
            posters[i].insert(posters[i].end(), passPosters.begin(), passPosters.end());
            if (--indegree[i] == 0)
            {
                que.emplace(i);
            }
        }
    }

    return !(pointsLeft);
}

int main()
{
    read(n); read(m); read(k);
    queries.reserve(k);
    while (m--)
    {
        int a, b;
        read(a); read(b);
        indegree[b]++;
        adj[a].emplace_back(move(b));
    }
    for (int i = 0; i != k; i++)
    {
        int a, b;
        read(a); read(b);
        if (a == b) queries.emplace_back(a, b, Status::NONE);
        else queries.emplace_back(a, b);
    }
    if (AOL() == true)
    {
        for (auto i : queries)
        {
            printf("%d\n", i.ans);
        }
    }
    else
    {
        printf("-1");
    }
    return 0;
}

