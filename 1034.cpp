#include <cstdio>

using namespace std;

int max(int a[], int left, int k, int N, int org)
{
	int m = 0, i = left;
	int l = left-1; if(l<0) l=N-1;
	if(a[l] < org) return org > a[(left+k)%N]? org: a[(left+k)%N];
	for(int j = 0; j < k; j++)
	{
		if(a[i] > m) m=a[i];
		i++; if(i >= N) i = 0;
	}
	return m;
}

int main()
{
	int N,K;
	int a[200000];
	scanf("%d%d",&N,&K);
	for(int i = 0; i < N; i++)
		scanf("%d",&a[i]);
	int m = -1;
	int ma = 0;
	for(int i = 0; i < N; i++)
	{
		ma = max(a,i,K,N,ma);
		if(ma < m || m==-1) m = ma;
	}
	printf("%d\n",m);
	return 0;
}
