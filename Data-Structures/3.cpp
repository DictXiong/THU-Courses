#include<iostream>

using namespace std;

int M,N;

int survive(int n)//n people, with first one has number 'mark'.
{
	return (n==1)? 1 : (((M-1)%n) + survive(n-1))%n + 1	;
}

int main()
{
	cin>>N>>M;
	cout<<survive(N);
	return 0;
}
