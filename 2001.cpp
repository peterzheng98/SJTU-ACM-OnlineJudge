#include <cstdio>

using namespace std;

int main()
{
	int n;
	int a[10001];
	a[0] = 0;
	scanf("%d",&n);
	for(int i = 1; i <= n; i++)
	{
		int b;
		scanf("%d",&b);
		a[i] = a[i-1]+b;
	}
	int m;
	scanf("%d",&m);
	for(int i = 0; i < m; i++)
	{
		int c,d;
		scanf("%d%d",&c,&d);
		printf("%d\n",a[d]-a[c-1]);
	}
	return 0;
}
