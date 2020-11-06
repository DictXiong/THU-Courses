#include<cstdio>
#include<utility>

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

const int N=100;
const int INF=0x3fffffff;

int n;
int map[N][N];

void floyd()
{
    for (int k=0;k!=n;k++)
        for (int i=0;i!=n;i++)
            for (int j=0;j!=n;j++)
                if (map[i][j] > map[i][k]+map[k][j])
                    map[j][i] = map[i][j] = map[i][k] + map[k][j]; 
}

pair<int,int> findAns()
{
    int ans=-1, minDis=INF;
    for (int i=0;i!=n;i++)
    {
        int maxDis=0;
        for (int j=0;j!=n;j++)
        {
            if (i!=j && map[i][j] > maxDis) maxDis=map[i][j];
        }
        if (maxDis < minDis) minDis=maxDis, ans=i;
    } 
    return make_pair(ans, minDis);
}

int main()
{
    int edge;
    read(n); read(edge);
    for (int i=0;i!=n;i++)
    {
        for (int j=0;j!=n;j++)
        {
            map[i][j]=INF;
        }   
        map[i][i]=0;
    } 
    while(edge--)
    {
        int a,b,c;
        read(a);read(b);read(c);
        a--;b--;
        map[a][b]=map[b][a]=c;
    }
    floyd();
    auto ans=findAns();
    printf("%d, max dis = %d", ans.first+1, ans.second);
}
