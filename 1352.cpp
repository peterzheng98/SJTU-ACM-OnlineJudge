#include <cstdio>

using namespace std;

int main()
{
	int m,n;
	scanf("%d%d",&m,&n);
	int S = m;
	int X;
	scanf("%d",&X);
	for(int i = 0; i < n-1; i++)
	{
		int k = m/X;
		if(m >= X)
		{
			m = m-k*X+k;
			S += k;
			scanf("%d",&X);
		}
	}
	while(m>=X)
	{
		int k = m/X;
		m = m-k*X+k;
		S += k;
	}
	printf("%d %d\n",S,m);
	return 0;
}
