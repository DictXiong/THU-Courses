#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;

//#define abs(a) (a>=0? a : -a)
#define max(a,b) (a>b ? a:b)

int abs(int a)
{
	return a >= 0 ? a : -a;
}

template<class T>void read(T& x)
{
	x = 0; char ch = getchar();
	while (ch < '0' || ch>'9') { ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	//x=f?-x:x;
	return;
}

class BinNode
{
public:
	int d;
	BinNode* lc, * rc;
	BinNode(int _d) :d(_d)
	{
		lc = rc = nullptr;
	}
};

class AVLTree
{
public:
	BinNode* root;
	AVLTree()
	{
		root = new BinNode(0);
	}
	void insert(int d)
	{
		BinNode* tmp = root;
		while (true)
		{
			if (d <= tmp->d)
			{
				if (tmp->lc == nullptr)
				{
					tmp->lc = new BinNode(d);
					break;
				}
				else tmp = tmp->lc;
			}
			else
			{
				if (tmp->rc == nullptr)
				{
					tmp->rc = new BinNode(d);
					break;
				}
				else tmp = tmp->rc;
			}
		}
	}
} tree;

vector<pair<int, int> > query;
vector<int> ans;
const int MAX = 60000;
bool visited[MAX];
int parent[MAX];

vector<pair<int, int> > findQuery(int n)
{
	vector<pair<int, int> > ans;
	auto size = query.size();
	for (auto i = 0; i != size; i++)
	{
		if (query[i].first == n) ans.push_back(make_pair(i, query[i].second));
		else if (query[i].second == n) ans.push_back(make_pair(i, query[i].first));
	}
	return ans;
}

int findParent(int n)
{
	return parent[n] = (parent[n] != n ? findParent(parent[n]) : n);
}

void tarjan(BinNode* node)
{
	if (node->lc != nullptr)
	{
		tarjan(node->lc);
		parent[node->lc->d] = node->d;
	}
	if (node->rc != nullptr)
	{
		tarjan(node->rc);
		parent[node->rc->d] = node->d;
	}
	visited[node->d] = true;
	auto q = findQuery(node->d);
	for (auto i : q)
	{
		if (visited[i.second])
		{
			ans[i.first] = findParent(i.second);
		}
	}
}

int main()
{
	int n, m, tmp, tmp2;
	read(n); read(m); read(tmp);
	tree.root->d = tmp;
	parent[tmp] = tmp;
	visited[tmp] = false;
	for (int i = 1; i != n; i++)
	{
		read(tmp);
		parent[tmp] = tmp;
		visited[tmp] = false;
		tree.insert(tmp);
	}

	ans.resize(m);
	for (int i = 0; i != m; i++)
	{
		read(tmp); read(tmp2);
		query.push_back(make_pair(tmp, tmp2));
	}
	tarjan(tree.root);

	for (auto i : ans) printf("%d\n", i);

	return 0;
}


