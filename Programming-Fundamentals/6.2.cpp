/* 
6.2 求一个长度不超过15的字符串的回文子序列个数（子序列长度>=1）。

样例输入
abaa

样例输出
10

注释
本例中其所有回文子序列为：
a,b,a,a,aba,aba,aa,aa,aa,aaa 
一个字符串的子序列是指在原字符串上去除某些字符但不破坏余下元素的相对位置（在前或在后）而形成的新字符串。
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
