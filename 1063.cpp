#include <cstdio>

using namespace std;

int d[500][500];
int h[500][500];

int D(int i, int j, int R, int C)
{
	if(d[i][j] >= 0) return d[i][j];
	int m = 1;
	if(i > 0 && h[i-1][j] < h[i][j])
	{
		int n = D(i-1,j,R,C);
		if(n+1>m) m = n+1;
	}
	if(j > 0 && h[i][j-1] < h[i][j])
	{
		int n = D(i,j-1,R,C);
		if(n+1>m) m = n+1;
	}
	if(i < R-1 && h[i+1][j] < h[i][j])
	{
		int n = D(i+1,j,R,C);
		if(n+1>m) m = n+1;
	}
	if(j < C-1 && h[i][j+1] < h[i][j])
	{
		int n = D(i,j+1,R,C);
		if(n+1>m) m = n+1;
	}
	d[i][j] = m;
	return d[i][j];
}

int main()
{
	int R,C;
	scanf("%d%d",&R,&C);
	for(int i = 0; i < R; i++)
		for(int j = 0; j < C; j++)
		{
			scanf("%d",&h[i][j]);
			d[i][j] = -1;
		}
	int m = 0;
	for(int i = 0; i < R; i++)
		for(int j = 0; j < C; j++)
			if(m < D(i,j,R,C)) m = d[i][j];
	printf("%d\n",m);
	return 0;
}
