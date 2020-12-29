/* 连击游戏
ACT Game 
在一个ACT Game当中，存在n种攻击技能，第i个攻击技能会造成ci的伤害。这些技能之间存在一些依赖关系，若技能j依赖于技能i，那么当前时刻使用技能i后，下一个时刻可以使用技能j。若技能j不依赖于技能i，那么当前时刻使用技能i后，下一个时刻将无法使用技能j。玩家在使用技能时必须从第一个技能开始到任意一个技能结束，构成一次技能流程，题目保证技能依赖不会出现循环。在游戏中，技能还分为物理和魔法两种属性，在一次技能释放的流程中，玩家可以在任何一个技能使用前选择使用物理加强或者魔法加强，物理加强使得之后的所有物理技能伤害翻倍但魔法伤害归0，魔法加强使得之后所有的魔法技能伤害翻倍但物理伤害归0，加强效果只能使用一次。现在给出这n种技能及其技能依赖关系，求玩家一次技能流程可以造成的最大伤害。

输入
第一行是攻击技能数量n，n<=100。 接下来给出一个n行n列的01矩阵M表示技能依赖关系，M[i,j]为1表示技能j依赖于技能i，M[i,j]为0表示技能j不依赖于技能i。 然后n行每行两个非负整数ci和ti，ci表示第i个技能的伤害，ti表示技能i的类型，ti为0代表物理技能，ti为1代表魔法技能。ci<=100000, ti<=1。

输出
求出玩家一次技能流程可以造成的最大伤害。

样例输入
8
0 1 1 0 0 0 0 0
0 0 0 1 1 0 0 0
0 0 0 0 1 0 0 0
0 0 0 0 0 0 1 0
0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0
4 0
1 1
4 0
2 1
7 1
1 0
0 0

样例输出
22

提示
转换为最短路方法求解。 每个顶点考虑是否使用加强可分成三种情况，综合答案即可。

** 这里使用了动态规划求解
*/

#include<cstdio>
#include<cstring>
using namespace std;
typedef unsigned int uint32;
typedef unsigned char uint8;

const int MAX_N = 102;
const int PHY = 0;
const int MAG = 1;
const int ORI = 2;

uint32 n;
uint32 adj[MAX_N][MAX_N];
size_t adj_size[MAX_N];
bool skill_type[MAX_N]; 
uint32 skill_damage[MAX_N];
int f[MAX_N][MAX_N][3]; // f[i][j][k]: 第 i 步, 走到了第 j 个点的时候, 已经采用了第 k 种增强, 
int ans = 0;

template<typename T>
inline T max(const T &a, const T &b)
{
    return (a>b)? a:b;
}

bool dp(uint32 step) // 返回是否有更新
{
    bool updated = false;
    int tmp;
    for (int i = 0; i != n+1; i++) // 遍历当前步的所有技能
    {
        for (int j = 0; j != 3; j++) // 遍历三种增强的选择
        {
            if (f[step][i][j] != -1) // 如果当前步有当前技能
            {
                updated = true;
                //for (const int &k:adj[i]) // 遍历后继技能
                for (int _k = 0; _k != adj_size[i]; _k++)
                {
                    int k = adj[i][_k];
                    if (j != ORI)
                    {
                        tmp = f[step][i][j] + (skill_type[k] == j ? skill_damage[k] * 2 : 0);
                        if (f[step + 1][k][j] < tmp)
                        {
                            f[step + 1][k][j] = tmp;
                            ans = max(ans, tmp);
                        }
                    }
                    else 
                    {
                        // 物理加强
                        tmp = f[step][i][j] + (skill_type[k] == PHY ? skill_damage[k] * 2 : 0);
                        if (f[step + 1][k][PHY] < tmp)
                        {
                            f[step + 1][k][PHY] = tmp;
                            ans = max(ans, tmp);
                        }
                        // 魔法加强
                        tmp = f[step][i][j] + (skill_type[k] == MAG ? skill_damage[k] * 2 : 0);
                        if (f[step + 1][k][MAG] < tmp)
                        {
                            f[step + 1][k][MAG] = tmp;
                            ans = max(ans, tmp);
                        }
                        // 不加强 (ans 一定不会在这儿)
                        tmp = f[step][i][j] + skill_damage[k];
                        f[step + 1][k][ORI] = max(f[step + 1][k][ORI], tmp);
                    }
                }
            }
        }
    }
    return updated;
}

int main()
{
    //freopen("D:\\test\\c++\\in", "r", stdin);
    scanf("%d", &n);
    int tmp1, tmp2;
    memset(adj_size, 0, sizeof(adj_size));
    bool skill_independent[MAX_N];
    memset(skill_independent, 1, sizeof(skill_independent));
    for (int i = 0; i != n; i++)
    {
        for (int j = 0; j != n; j++)
        {
            scanf("%d", &tmp1);
            if (tmp1)
            {
                adj[i][adj_size[i]++] = j;
                skill_independent[j] = false;
            } 
            // initializaton of f
            f[i][j][0] = f[i][j][1] = f[i][j][2] = -1;
        }
        f[i][n][0] = f[i][n][1] = f[i][n][2] = -1;
    }
    for (int i = 0; i != n; i++)
    {
        scanf("%d %d", &tmp1, &tmp2);
        skill_damage[i] = tmp1;
        skill_type[i] = tmp2;
    }
    // making super node n
    for (int i = 0; i != n; i++)
    {
        if (skill_independent[i])
        {
            adj[n][adj_size[n]++] = i;
        }
    }
    skill_type[n] = 0;
    skill_damage[n] = 0;
    f[0][n][ORI] = f[0][n][PHY] = f[0][n][MAG] = 0;
    for (int i = 0; i != n + 1; i++)
    {
        if (!dp(i)) break;
    }
    printf("%d", ans);
    return 0;
}