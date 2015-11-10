#include <iostream>
#include <cstdio>

using namespace std;

int C[12346], S[12346], F[123456];

void preorder(int t)
{
	printf("%d ",t);
	for(int k = C[t]; k; k=S[k])
		preorder(k);
}

void postorder(int t)
{
	for(int k = C[t]; k; k=S[k])
		postorder(k);
	printf("%d ",t);
}

void layer(int t)
{
	int Q[12346],p=0,q=0;
	Q[q++] = t;
	while(p<q)
	{
		int r = Q[p++];
		for(int k=C[r];k;k=S[k])
			Q[q++]=k;
		printf("%d ",r);
	}
}

int main()
{
	int N;
	scanf("%d",&N);
	for(int i = 1; i <= N; i++)
		F[i] = 0;
	for(int i = 0; i < N; i++)
	{
		int x,Cx,Sx;
		scanf("%d%d%d",&x,&Cx,&Sx);
		C[x]=Cx;S[x]=Sx;
		F[Cx]=x;F[Sx]=x;
	}
	int r = 1;
	while(F[r]) r=F[r];
	preorder(r);
	printf("\n");
	postorder(r);
	printf("\n");
	layer(r);
	printf("\n");
	return 0;
}
