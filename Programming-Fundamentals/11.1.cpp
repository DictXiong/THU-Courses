/*
这其实是我写过的第一个链表, 20min一次ac. 

4007_学生信息管理
描述
编写一个程序，首先根据用户的输入信息创建一条链表LA，每个链表结点的内容为学生的学号（正整数），各结点之间按学号升序排列。然后再根据用户的输入信息创建另一条链表LB，每个链表结点包括学生的学号S和一个运算符O，O的值为“增加”或“删除”。接下来，程序将对LB的每个结点进行分析，如果O的值为“增加”，则在链表LA中新增一个结点，其学号即为S；如果O的值为“删除”，则在链表LA中，找到学号为S的结点并将其删除。在经过上述处理后，要求LA中的结点依然按学号升序排列。

说明：（1）在创建链表时，为了减少内存空间的浪费，必须采用 动态链表 的方法，即每一个链表结点都是根据需要动态创建的；（2）为了增强程序的可读性，应采用多函数的形式来实现，至少应包含如下的函数：创建链表、打印链表等。

输入
第一行是一个整数M，表示链表LA的结点个数，接下来有M行，每一行是一个整数si，表示第i个结点的学号（按照从小到大排序）。接下来的一行是一个整数N，表示链表LB的结点个数，再接下来有N行，每一行是两个整数si和oi，其中，si表示第i个结点的学号（按照从小到大排序），oi表示运算符，oi=1表示“增加”结点，oi =0表示“删除”结点。

输出
输出经过处理以后的链表LA的内容。假设该链表共有K个结点，则输出有K行，每一行是一个整数，即相应的学号。

输入样例
4
1001
1003
1005
1007
2
1002 1
1007 0
输出样例
1001
1002
1003
1005
*/

#include<iostream>
#include<cstdio> 

using namespace std;

struct node
{
	int id;
	node* next=NULL;
} root,tail;

void init()
{
	root.id=0;
	root.next=&tail;
	tail.id=0x3F3F3F3F;
}

void push(int id)
{
	node* n=(node*)malloc(sizeof(node));
	n->id=id;
	for (node* i=&root;i!=&tail;i=i->next)
	{
		if (id<i->next->id) 
		{
			n->next=i->next;
			i->next=n;
			return;
		}
	}
}

void del(int id)
{
	for (node* i=&root;i!=&tail;i=i->next)
	{
		if (i->next->id==id)
		{
			node *tmp=i->next->next;
			free(i->next);
			i->next=tmp;
			return;
		}
	}
}

void print()
{
	for (node* i=root.next;i!=&tail;i=i->next)
	{
		cout<<i->id<<endl;
	}
}

int main()
{
	init();
	int n;cin>>n;
	for (int i=0;i!=n;i++)
	{
		int tmp;
		cin>>tmp;
		push(tmp);
	}
	cin>>n;
	for (int i=0;i!=n;i++)
	{
		int tmp,ins;
		cin>>tmp>>ins;
		if (ins==1) push(tmp);
		if (ins==0) del(tmp);
	}
	print();
}
