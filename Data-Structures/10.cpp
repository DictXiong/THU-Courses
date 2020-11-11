#include<iostream>
#include<stack>
using namespace std;

#define max(a,b) (a>b ? a:b)

int deltaX[]={0,1,0,-1};
int deltaY[]={1,0,-1,0};

const int MAX=1001;
int m,n;
bool map[MAX][MAX];
bool visited[MAX][MAX];

inline bool lawful(int x,int y)
{
    return (x>=0 && y>=0 && x<m && y<n);
}

int solve(int x, int y)
{
    if (x<0 || y<0 || x>=m || y>=n) exit(20);
    int ans=0;
    if (visited[x][y]) return 0;
    
    stack<pair<int,int> > fuck;
    fuck.push(make_pair(x,y));
    visited[x][y]=1;
    while (!fuck.empty())
    {
        x=fuck.top().first;
        y=fuck.top().second;
        //cout<<x<<" "<<y<<endl;
        fuck.pop();
        ans++;
        for (int i=0;i!=4;i++)
        {
            int toX,toY;
            toX=x+deltaX[i];
            toY=y+deltaY[i];
            if (lawful(toX,toY))
                if (map[toX][toY] && !visited[toX][toY])
                {
                    fuck.push(make_pair(toX,toY));
                    visited[toX][toY]=1;
                }
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin>>m>>n;
    bool tmp;
    char ch;
    for (int i=0;i!=m;i++)
    {
        for (int j=0;j!=n;j++)
        {
            cin>>ch;
            map[i][j]= (ch == '1');
            visited[i][j]=false;
        }
    }
    int ans=0;
    for (int i=0;i!=m;i++)
    {
        for (int j=0;j!=n;j++)
        {
            if (map[i][j] && !visited[i][j])
            {
                int tmp=solve(i,j);
                ans=max(ans,tmp);
            }
        }
    }
    cout<<ans;
    return 0;
}
