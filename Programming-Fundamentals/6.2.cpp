/* 
6.2 ��һ�����Ȳ�����15���ַ����Ļ��������и����������г���>=1����

��������
abaa

�������
10

ע��
�����������л���������Ϊ��
a,b,a,a,aba,aba,aa,aa,aa,aaa 
һ���ַ�������������ָ��ԭ�ַ�����ȥ��ĳЩ�ַ������ƻ�����Ԫ�ص����λ�ã���ǰ���ں󣩶��γɵ����ַ�����
*/


#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

int main()
{
	int n; string s;
	cin>>s;
	n=s.length();
	int f[15][15],ans=0;
	memset(f,0,sizeof(f));
	for (int i=0;i!=n;i++)
	{
		f[i][i]=1;
	}
	for (int j=1;j!=n;j++)
	{
		for (int i=0;i!=j;i++)
		{
			f[i][j]=f[i][j-1]+1;
			for (int k=i;k!=j;k++)
			{
				if (s[k]!=s[j]) continue;
				f[i][j]+=1;
				f[i][j]+= k==j-1? 0:f[k+1][j-1];
			}
			if (j==n-1)
			{
				cout<<f[0][j];
				return 0;
			}
		}
	}
}
