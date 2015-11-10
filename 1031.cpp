#include <cstdio>

using namespace std;

void update(int m[100][100], int h[100][100], int l[100][100], int p, int q, int N)
{
	if(p > 0)
	{
		int H = h[p][q], L = l[p][q];
		if(m[p-1][q] > H) H = m[p-1][q];
		if(m[p-1][q] < L) L = m[p-1][q];
		if(H-L < h[p-1][q]-l[p-1][q])
		{
			h[p-1][q] = H;
			l[p-1][q] = L;
			update(m,h,l,p-1,q,N);
		}
	}
	if(q > 0)
	{
		int H = h[p][q], L = l[p][q];
		if(m[p][q-1] > H) H = m[p][q-1];
		if(m[p][q-1] < L) L = m[p][q-1];
		if(H-L < h[p][q-1]-l[p][q-1])
		{
			h[p][q-1] = H;
			l[p][q-1] = L;
			update(m,h,l,p,q-1,N);
		}
	}
	if(p < N-1)
	{
		int H = h[p][q], L = l[p][q];
		if(m[p+1][q] > H) H = m[p+1][q];
		if(m[p+1][q] < L) L = m[p+1][q];
		if(H-L < h[p+1][q]-l[p+1][q])
		{
			h[p+1][q] = H;
			l[p+1][q] = L;
			update(m,h,l,p+1,q,N);
		}
	}
	if(q < N-1)
	{
		int H = h[p][q], L = l[p][q];
		if(m[p][q+1] > H) H = m[p][q+1];
		if(m[p][q+1] < L) L = m[p][q+1];
		if(H-L < h[p][q+1]-l[p][q+1])
		{
			h[p][q+1] = H;
			l[p][q+1] = L;
			update(m,h,l,p,q+1,N);
		}
	}
}

int main()
{
	int N;
	int m[100][100];
	scanf("%d",&N);
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			scanf("%d",&m[i][j]);
	int h[100][100];
	int l[100][100];
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
		{
			h[i][j] = 10000;
			l[i][j] = -1;
		}
	h[0][0] = m[0][0];
	l[0][0] = m[0][0];
	update(m,h,l,0,0,N);
	printf("%d\n",h[N-1][N-1]-l[N-1][N-1]);
	return 0;
}
