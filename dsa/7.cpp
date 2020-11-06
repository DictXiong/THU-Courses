#include <string>
#include <queue>
using namespace std;

const int CHARMAX=256;

class Elem
{
public:
	int count;
	string s;
	Elem(int _c, string _s):count(_c),s(_s){
	}
	Elem(int _c, char _ch):count(_c),s(1,_ch){
	}
	bool operator<(Elem e)const
	{
		return count>e.count;
	}
	bool operator>(Elem e)const
	{
		return e<*this;
	}
	Elem operator+(Elem e)const
	{
		return Elem(count+e.count, s+e.s);
	}
};

priority_queue<Elem> que;

int main()
{
    string input;
    int freq[CHARMAX];
    for (int i = 0; i != CHARMAX; i++) freq[i] = 0;
    char c;
    while((c=getchar())!='\n')
	{
		freq[c+128]++;
		input+=c;
	}
    
    //从freq数组计算哈夫曼编码位数
    for (int i=0;i!=CHARMAX;i++)
    {
    	if (freq[i]!=0)
    	{
    		que.push(Elem(freq[i],char(i-128)));
    		freq[i]=0;
		}
	}
	
	if (que.size()==1)
	{
		printf("%d",input.size());
		return 0;
	}
	
    while(que.size()>1)
    {
    	Elem tmp1=que.top();
		que.pop();
		Elem tmp2=que.top();
		que.pop();
		Elem comb=tmp1+tmp2;
		string s=comb.s;
		que.push(comb);
		for (char i:s)
		{
			freq[i+128]++;
		}
	}
	
	int ans=0;
	for (char i:input)
	{
		ans+=freq[i+128];
	}
	printf("%d",ans);
	return 0;
}
