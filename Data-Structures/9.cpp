#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<tuple>
using namespace std;

template<class T>void read(T& x)
{
    x = 0; char ch = getchar();
    while (ch < '0' || ch>'9') { ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    //x=f?-x:x;
    return;
}

const int INF = 0x3FFFFFFF;

enum class Dim
{
    row = 0, col = 1
};

Dim switchDim(const Dim& d)
{
    return Dim(!bool(d));
}

class Point
{
public:
    double x, y;

    Point(const double& _x = 0, const double& _y = 0) : x(_x), y(_y) {}
    double distance(const Point& p)const
    {
        return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
    }
    double distance(const Point& p, const Dim& d)const
    {
        return (d == Dim::row ? abs(x - p.x) : abs(y - p.y));
    }
    double getAxis(const Dim& d)const
    {
        return (d == Dim::row ? x : y);
    }

};
typedef vector<Point> PointVec;

bool compRow(const Point& a, const Point& b)
{
    return (a.x != b.x ? (a.x > b.x) : (a.y > b.y));
}

bool compCol(const Point& a, const Point& b)
{
    return (a.y != b.y ? (a.y > b.y) : (a.x > b.x));
}

tuple< Point, PointVec, PointVec > split(const PointVec& p, const Dim& d)
{
    PointVec tmp = p;
    sort(tmp.begin(), tmp.end(), (d == Dim::row ? compRow : compCol));
    auto midPos = tmp.size() / 2;
    return make_tuple(tmp.at(midPos), PointVec(tmp.begin(), tmp.begin() + midPos), PointVec(tmp.begin() + midPos + 1, tmp.end()));
}

class Node
{
public:
    Point p;
    Node* lc = nullptr, * rc = nullptr;
    Node(const double& x, const double& y) : p(x, y) {}
    Node(const Point& _p) : p(_p) {}
};

class Tree
{
public:
    Node* root;
    Tree(const PointVec& points)
    {
        root = build(points, Dim::row);
    }

    Node* build(const PointVec& points, Dim d)
    {
        auto tmp = split(points, d);
        Node* mid = new Node(get<0>(tmp));
        if (!get<1>(tmp).empty()) mid->lc = build(get<1>(tmp), switchDim(d));
        if (!get<2>(tmp).empty()) mid->rc = build(get<2>(tmp), switchDim(d));
        return mid;
    }

    inline double nearest(const Point& p)const
    {
        return nearest(p, root, Dim::row, INF);
    }

    double nearest(const Point& p, const Node* node, const Dim& d, double ansNow)const
    {
        ansNow = min(ansNow, node->p.distance(p));
        double tmpAns;
        if (p.getAxis(d) >= node->p.getAxis(d))
        {
            if (node->lc)
            {
                tmpAns = nearest(p, node->lc, switchDim(d), ansNow);
                ansNow = min(ansNow, tmpAns);
            }
            if (node->rc && (ansNow > node->p.distance(p, d)))
            {
                tmpAns = nearest(p, node->rc, switchDim(d), ansNow);
                ansNow = min(ansNow, tmpAns);
            }
        }
        else
        {
            if (node->rc)
            {
                tmpAns = nearest(p, node->rc, switchDim(d), ansNow);
                ansNow = min(ansNow, tmpAns);
            }
            if (node->lc && (ansNow > node->p.distance(p, d)))
            {
                tmpAns = nearest(p, node->lc, switchDim(d), ansNow);
                ansNow = min(ansNow, tmpAns);
            }
        }
        return ansNow;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    double x, y;
    char c;
    PointVec points;
    for (int i = 0; i != n; i++)
    {
        cin >> x >> y >> c;
        points.push_back(Point(x, y));
    }
    Tree tree(points);
    for (int i = 0; i != m; i++)
    {
        cin >> x >> y;
        cout<<fixed<<setprecision(4)<<tree.nearest(Point(x, y))<<endl;
    }
    return 0;
}
