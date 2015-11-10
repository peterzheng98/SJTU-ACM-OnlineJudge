#include <cstdio>
#include <map>

using namespace std;

map<long long int,int> FF;

int F(long long int n)
{
	if(n == 0) return 0;
	if(n < 3) return 1;
	if(FF.find(n) != FF.end())
		return FF[n];
	long long int n1 = n/2, n2 = n-n1;
	if(n1 == n2)
	{
		int Fn1 = F(n1);
		int res = ((2*F(n1-1)+Fn1)*Fn1) % 2010;
		FF[n] = res;
		return res;
	}
	int Fn1 = F(n1), Fn2 = F(n2);
	int res = (Fn1*Fn1+Fn2*Fn2)%2010;
	FF[n] = res;
	return res;
}

int main()
{
	long long int N;
	scanf("%lld",&N);
	printf("%d\n",F(N));
	return 0;
}
