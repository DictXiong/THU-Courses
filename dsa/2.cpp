#include<iostream>
#include<vector> 
#include<cstring>
using namespace std;

class BigInt
{
	private:
		vector<short> _num;
		void _add(int pos,int num)
		{
			if (pos>=_num.size()) _num.resize(pos+1);
			_num[pos]+=num;
			if (_num[pos]>=10) _add(pos+1,_num[pos]/10),_num[pos]%=10;
		}
	public:
		BigInt(){}
		BigInt(string s)
		{
			for (int i=s.size()-1;i>=0;i--)
			{
				_num.push_back(s[i]-'0');
			}
		}
		BigInt operator *(BigInt bi2)
		{
			BigInt ans;
			for (int i=0;i!=_num.size();i++)
				for (int j=0;j!=bi2._num.size();j++)
				{
					ans._add(i+j,_num[i]*bi2._num[j]);
				}
			return ans;
		}
		friend ostream & operator<<(ostream &out, BigInt& bi);
		friend istream & operator>>(istream &in, BigInt& bi);
};

ostream & operator<<(ostream &out, BigInt & bi)
{
	for (int i=bi._num.size()-1;i>=0;i--)
	{
		out<<bi._num[i];
	}
	return out;
}

istream & operator>>(istream &in, BigInt &bi)
{
	string s;
	in>>s;
	bi=(BigInt)s;
	return in;
}

int main()
{
	BigInt a,b;
	int n;
	cin>>n;
	BigInt c;
	for (int i=0;i!=n;i++)
	{
		cin>>a>>b;
		c=a*b;
		cout<<c<<endl;
	}
	return 0;
}
