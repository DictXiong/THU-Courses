/*
����ʵ����д���ĵ�һ������, 20minһ��ac. 

4007_ѧ����Ϣ����
����
��дһ���������ȸ����û���������Ϣ����һ������LA��ÿ�������������Ϊѧ����ѧ�ţ����������������֮�䰴ѧ���������С�Ȼ���ٸ����û���������Ϣ������һ������LB��ÿ�����������ѧ����ѧ��S��һ�������O��O��ֵΪ�����ӡ���ɾ�����������������򽫶�LB��ÿ�������з��������O��ֵΪ�����ӡ�����������LA������һ����㣬��ѧ�ż�ΪS�����O��ֵΪ��ɾ��������������LA�У��ҵ�ѧ��ΪS�Ľ�㲢����ɾ�����ھ������������Ҫ��LA�еĽ����Ȼ��ѧ���������С�

˵������1���ڴ�������ʱ��Ϊ�˼����ڴ�ռ���˷ѣ�������� ��̬���� �ķ�������ÿһ�������㶼�Ǹ�����Ҫ��̬�����ģ���2��Ϊ����ǿ����Ŀɶ��ԣ�Ӧ���öຯ������ʽ��ʵ�֣�����Ӧ�������µĺ���������������ӡ����ȡ�

����
��һ����һ������M����ʾ����LA�Ľ���������������M�У�ÿһ����һ������si����ʾ��i������ѧ�ţ����մ�С�������򣩡���������һ����һ������N����ʾ����LB�Ľ��������ٽ�������N�У�ÿһ������������si��oi�����У�si��ʾ��i������ѧ�ţ����մ�С�������򣩣�oi��ʾ�������oi=1��ʾ�����ӡ���㣬oi =0��ʾ��ɾ������㡣

���
������������Ժ������LA�����ݡ������������K����㣬�������K�У�ÿһ����һ������������Ӧ��ѧ�š�

��������
4
1001
1003
1005
1007
2
1002 1
1007 0
�������
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
