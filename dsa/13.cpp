#include<cstdio>
#include<utility>
#include<vector>
using namespace std;

#include<initializer_list>
template<class T>inline void read(T& x)
{
    x = 0; int f = 0; char ch = getchar();
    while (ch < '0' || ch>'9') { f |= (ch == '-'); ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    x = f ? -x : x;
    return;
}
template<typename T>
inline void readd(T& t)
{
    read(t);
}
template <typename T, typename... args>
inline void readd(T& t, args&... rest)
{
    read(t);
    readd(rest...);
}


class Point
{
public:
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
    Point() = default;

    inline Point operator+(const Point& a)const
    {
        return Point(x + a.x, y + a.y);
    }
    inline Point operator-(const Point& a)const
    {
        return Point(x - a.x, y - a.y);
    }
    inline bool operator==(const Point& a)const
    {
        return x == a.x && y == a.y;
    }
    inline bool coline(const Point& a)const
    {
        return (x * a.y == y * a.x);
    }
};

const int MOD = 119997;
inline int hashPoint(const Point& a)
{
    return (((a.x) * 1000 + (a.y) * 1234) % MOD + MOD) % MOD;
}

struct ListElem
{
    Point sum,slope;
    ListElem() = default;
    ListElem(const Point& a, const Point& b) : sum(a+b), slope(a-b){}
};
vector<ListElem> hashTable[MOD];

void initTable()
{
    for (int i = 0; i != MOD; i++)
    {
        hashTable[i].clear();
    }
}

inline void insertTable(const Point& a, const Point& b)
{
    auto pos = hashPoint(a+b);
    hashTable[pos].emplace_back(a, b);
}

int selfCheck()
{
    int ans = 0;
    for (int i = 0; i != MOD; i++)
    {
        auto size = hashTable[i].size();
        if (size>=2)
        {
            for (auto j = 0; j!=size-1; j++)
            {
                for (auto k = j; k != size; k++)
                {
                    if (hashTable[i][j].sum == hashTable[i][k].sum && !hashTable[i][j].slope.coline(hashTable[i][k].slope)) ans++;
                }
            }
        }
    }
    return ans;
}

const int MAX = 400;
Point points[MAX];

int main()
{
    int n, m;
    read(n);
    vector<int> ansList;
    ansList.reserve(n);
    while (n--)
    {
        read(m);
        initTable();
        for (int i = 0; i != m; i++)
        {
            Point tmp;
            //readd(tmp.x, tmp.y);
            read(tmp.x);
            read(tmp.y);
            points[i] = tmp;
        }
        for (int i = 0; i != m-1; i++)
        {
            for (int j = i; j != m; j++)
            {
                insertTable(points[i], points[j]);
            }
        }
        ansList.push_back(selfCheck());
    }
    for (auto i : ansList)
    {
        printf("%d\n", i);
    }
}

