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
	int d, h;
	BinNode* lc, * rc, * pr;
	BinNode(int _d, BinNode* _pr) :d(_d), pr(_pr)
	{
		lc = rc = nullptr;
		h = 0;
	}
};

inline int height(BinNode* node)
{
	return node == nullptr ? -1 : node->h;
}

class AVLTree
{
public:
	BinNode* root;
	AVLTree()
	{
		root = new BinNode(0, nullptr);
	}
	void setHeight(BinNode* node, int height)
	{
		if (node != nullptr && (node->h < height))
		{
			node->h = height;
			setHeight(node->pr, height + 1);
		}
	}
	void updateHeight(BinNode* node)
	{
		if (node != nullptr)
		{
			node->h = max(height(node->lc), height(node->rc)) + 1;
			updateHeight(node->pr);
		}
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
					tmp->lc = new BinNode(d, tmp);
					break;
				}
				else tmp = tmp->lc;
			}
			else
			{
				if (tmp->rc == nullptr)
				{
					tmp->rc = new BinNode(d, tmp);
					break;
				}
				else tmp = tmp->rc;
			}
		}
		setHeight(tmp, 1);
		BinNode* g = tmp->pr, * p = tmp;
		while (g != nullptr && (abs(height(g->lc) - height(g->rc)) < 2))
		{
			p = g; g = g->pr;
		}
		if (g != nullptr)
		{
			if (p == g->rc)
			{
				if (height(p->rc) >= height(p->lc)) zag(g);
				else
				{
					zig(p);
					zag(g);
				}
			}
			else if (p == g->lc)
			{
				if (height(p->lc) >= height(p->rc)) zig(g);
				else
				{
					zag(p);
					zig(g);
				}
			}
		}
	}
	void zag(BinNode* v)
	{
		BinNode* rc = (v->rc);
		swap(rc->d, v->d);
		v->rc = rc->rc;
		if (v->rc != nullptr) v->rc->pr = v;

		rc->rc = rc->lc;
		//rc->rc->pr=rc;

		rc->lc = v->lc;
		if (rc->lc != nullptr) rc->lc->pr = rc;

		v->lc = rc;
		//v->lc->pr=v;

		rc->h = max(height(rc->lc), height(rc->rc)) + 1;
		v->h = -1;
		updateHeight(v);
	}
	void zig(BinNode* v)
	{
		BinNode* lc = (v->lc);
		swap(v->d, lc->d);
		v->lc = lc->lc;
		if (v->lc != nullptr) v->lc->pr = v;

		lc->lc = lc->rc;

		lc->rc = v->rc;
		if (lc->rc != nullptr) lc->rc->pr = lc;

		v->rc = lc;

		lc->h = max(height(lc->lc), height(lc->rc))+1;
		v->h = -1;
		updateHeight(v);
	}
	void print(BinNode* node)
	{
		if (node)
		{
			printf("Node %d, height %d, sons: %d, %d. \n", node->d, node->h, node->lc == nullptr ? -1 : node->lc->d, node->rc == nullptr ? -1 : node->rc->d);
			print(node->lc); print(node->rc);
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
	//return log(m)*10;
	tree.root->d = tmp;
	parent[tmp] = tmp;
	visited[tmp] = false;
	for (int i = 1; i != n; i++)
	{
		read(tmp);
		parent[tmp] = tmp;
		visited[tmp] = false;
		tree.insert(tmp);
		//printf("insert: %d\n", tmp);
		//tree.print(tree.root);
		//printf("----------------------------\n\n");
	}

	ans.resize(m);
	for (int i = 0; i != m; i++)
	{
		read(tmp); read(tmp2);
		query.push_back(make_pair(tmp, tmp2));
	}
	//tree.print(tree.root);
	tarjan(tree.root);

	for (auto i:ans) printf("%d\n",i);

	return 0;
}


