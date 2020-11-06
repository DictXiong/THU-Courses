#include<cstdio>
#include<map>
#include<queue>
#include<tuple>
#include<cstring>
#define likely(x) __builtin_expect(!!(x), 1) // x is likely to be true       
#define unlikely(x) __builtin_expect(!!(x), 0) // x is likely to be false

#define test

using namespace std;

template<class T>void read(T &x)
{
    x=0;int f=0;char ch=getchar();
    while(ch<'0'||ch>'9')  {f|=(ch=='-');ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;
    return;
}

template<typename t>
inline t abs(const t& a)
{
    return (a >= 0 ? a : -a);
}

const int INF = 0x3FFFFFFF;
int dim, n, imax;

class Point
{
private:
    int* _axis;
public:
    Point()
    {
        _axis = new int[dim];
    }
    Point(const Point& p)
    {
        _axis = new int[dim];
        for (int i = 0; i != dim; i++)
        {
            _axis[i] = p._axis[i];
        }
    }
    ~Point()
    {
        delete[] _axis;
    }
    int& operator[](const size_t& pos)
    {
        return _axis[pos];
    }
    const int& operator[](const size_t& pos)const
    {
        return _axis[pos];
    }
    const Point& operator=(const Point& p)
    {
        for (int i = 0; i != dim; i++)
        {
            _axis[i] = p._axis[i];
        }
        return *this;
    }
};

class Elem
{
public:
    int dis;
    int point;
    Elem(int _dis, int _point) :dis(_dis), point(_point) {}
    bool operator<(const Elem& d)const
    {
        return dis < d.dis;
    }
    bool operator>(const Elem& d)const
    {
        return dis > d.dis;
    }
};

priority_queue<Elem> maxQue[32];
priority_queue<Elem, vector<Elem>, greater<Elem> > minQue[32];
bool* deleted;

inline int getMax()
{
    int ans = 0;
    for (int i = 0; i != imax; i++)
    {
        while (!maxQue[i].empty() && deleted[maxQue[i].top().point]) maxQue[i].pop();
        while (!minQue[i].empty() && deleted[minQue[i].top().point]) minQue[i].pop();
        if (maxQue[i].empty() || minQue[i].empty()) continue;
        ans = max(ans, maxQue[i].top().dis - minQue[i].top().dis);
    }
    return ans;
}

int main()
{
#ifdef test
    vector<int> ans;
#endif
    read(n); read(dim);
    ans.reserve(n);
    imax = 1 << dim;
    deleted = new bool[n];
    memset(deleted, 0, n * sizeof(bool));
    for (int i = 0; i != n; i++)
    {
        bool op;
        read(op);
        if (likely(op == 0))
        {
            Point p;
            for (int j = 0; j != dim; j++)
            {
                read(p[j]);
            }
            for (int j = 0; j != imax; j++)
            {
                int sum = 0;
                for (int k = 0; k != dim; k++)
                {
                    sum += (1 << k & j) ? +p[k] : -p[k];
                }
                maxQue[j].push(Elem(sum, i));
                minQue[j].push(Elem(sum, i));
            }
#ifdef test
            ans.push_back(getMax());
#else
            printf("%d\n", getMax());
#endif
        }
        else
        {
            int point;
            read(point);
            point--;
            deleted[point] = true;
#ifdef test
            ans.push_back(getMax());
#else
            printf("%d\n", getMax());
#endif
        }
    }
    delete[] deleted;
#ifdef test
    for (auto i : ans)
        printf("%d\n", i);
#endif
}
