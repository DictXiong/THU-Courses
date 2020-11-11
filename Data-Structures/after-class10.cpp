#include<iostream>
#include<queue>
#include<vector>
using namespace std;

int n;
const int N = 10, INF = 0x3fffffff;
vector<pair<int,int>> adj[N];
int dis[N];

void SPFA(int start)
{
    for (int i=0; i!=n; i++)
        dis[i] = INF;
    dis[start] = 0;
    vector<bool> inque;
    inque.resize(n);
    queue<int> que;
    que.push(start);
    while(!que.empty())
    {
        int now = que.front(); que.pop();
        inque[now] = false;
        for (auto i : adj[now])
        {
            if (dis[now] + i.second < dis[i.first])
            {
                dis[i.first] = dis[now] + i.second;
                if (!inque[i.first]) que.push(i.first), inque[i.first] = true;
            }
        }
    }
}

int main()
{
    int m;
    cin>>n>>m;
    while(m--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        a--;b--;
        adj[a].push_back(make_pair(b,c));
    }
    SPFA(0);
    for (int i=0;i!=n;i++)
    {
        cout<<dis[i]<<endl;
    }
    return 0;
}
