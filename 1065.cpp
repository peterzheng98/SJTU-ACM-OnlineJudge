#include <cstdio>
#include <cstring>

#define max(a,b,c) ((a)>(b)?((a)>(c)?(a):(c)):((b)>(c)?(b):(c)))

using namespace std;

int main()
{
	char a[1002],b[1002];
	scanf("%s%s",a+1,b+1);
	int m = strlen(a+1), n = strlen(b+1);
	int c[1001][1001];
	for(int i = 0; i <= m; i++)
		c[i][0] = 0;
	for(int j = 0; j <= n; j++)
		c[0][j] = 0;
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			int e = c[i-1][j];
			int f = c[i][j-1];
			int g = c[i-1][j-1] + (a[i]==b[j]?1:0);
			c[i][j] = max(e,f,g);
		}
	}
	printf("%d\n",c[m][n]);
	return 0;
}
