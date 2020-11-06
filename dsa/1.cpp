#include<iostream>
using namespace std;
const int N=25000;

class Vector
{
	public:
		int x,y;
		Vector()
		{
			x=y=0;
		}
		Vector(int _x,int _y)
		{
			x=_x,y=_y;
		}
		bool operator>(Vector v)
		{
			return (x!=v.x)?(x>v.x) : (y>v.y);
		}
		bool operator<(Vector v)
		{
			return v>(*this);
		}
		bool operator==(Vector v)
		{
			return x==v.x&&y==v.y;
		} 
};

class VectorSet
{
	public:
		Vector queue[N];
		int size=0;
		void insert(int pos,Vector v)
		{
			for (int i=size;i>pos;i--)
			{
				queue[i]=queue[i-1];
			}
			queue[pos]=v;
		}
		void push(Vector v)
		{
			for (int i=size-1;i>=0;i--)
			{
				if (v>queue[i])
				{
					size++;
					insert(i+1,v);
					return;
				}
				else if (v==queue[i]) return;
			}
			size++;
			insert(0,v);
		}
		void print()
		{
			for (int i=0;i!=size;i++)
			{
				cout<<queue[i].x<<" "<<queue[i].y<<endl; 
			}
		}
} vectorSet;

int main()
{
	int n;
	cin>>n;
	for (int i=0;i!=n;i++)
	{
		int a,b;
		cin>>a>>b;
		vectorSet.push(Vector(a,b));
	}
	vectorSet.print();
}
