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

    Point operator+(const Point& a)const
    {
        return Point(x + a.x, y + a.y);
    }
    Point operator-(const Point& a)const
    {
        return Point(x - a.x, y - a.y);
    }
    bool operator==(const Point& a)const
    {
        return x == a.x && y == a.y;
    }
    bool coline(const Point& a)const
    {
        return (x * a.y == y * a.x);
    }
};

const int MOD = 119997;
int hashPoint(const Point& a)
{
    return (((a.x) * 1000 + (a.y) * 1234) % MOD + MOD) % MOD;
}

struct ListElem
{
    Point sum,slope; ListElem* next;
    ListElem() = default;
    ListElem(const Point& a, const Point& b) : sum(a+b), slope(a-b), next(nullptr) {}
    ~ListElem()
    {
        if (next != nullptr) delete next;
    }
};
ListElem* hashTable[MOD];

void initTable()
{
    for (int i = 0; i != MOD; i++)
    {
        if (hashTable[i] != nullptr) delete hashTable[i];
        hashTable[i] = nullptr;
    }
}

void insertTable(const Point& a, const Point& b)
{
    auto pos = hashPoint(a+b);
    if (hashTable[pos] != nullptr)
    {
        auto parent = hashTable[pos];
        while (parent->next) parent = parent->next;
        parent->next = new ListElem(a,b);
    }
    else
    {
        hashTable[pos] = new ListElem(a,b);
    }
}

int checkTable(const Point& a, const Point &b)
{
    auto pos = hashPoint(a+b);
    int ans = 0;
    for (auto elem = hashTable[pos]; elem != nullptr; elem = elem->next)
    {
        if (!elem->slope.coline(a-b)) ans++;
    }
    return ans;
}

int selfCheck()
{
    int ans = 0;
    for (int i = 0; i != MOD; i++)
    {
        if (hashTable[i] != nullptr && hashTable[i]->next != nullptr)
        {
            for (auto j = hashTable[i]; j->next != nullptr; j = j->next)
            {
                for (auto k = j->next; k != nullptr; k = k->next)
                {
                    if (j->sum == k->sum && !j->slope.coline(k->slope)) ans++;
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
            readd(tmp.x, tmp.y);
            points[i] = tmp;
        }
        for (int i = 0; i != m-1; i++)
        {
            for (int j = i; j != m; j++)
            {
                insertTable(points[i], points[j]);
            }
        }
        /*
        int ans = 0;
        for (int i = 0; i != m - 1; i++)
            for (int j = i; j != m; j++)
                ans += checkTable(points[i], points[j]);
        ansList.push_back(ans / 2);
        */
        ansList.push_back(selfCheck());
    }
    for (auto i : ansList)
    {
        printf("%d\n", i);
    }
}

