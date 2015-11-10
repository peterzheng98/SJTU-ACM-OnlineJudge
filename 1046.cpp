#include <iostream>
#include <cstdio>

using namespace std;

int L[100001],R[100001],F[100001],C[100001],NR[100001],S[100001];

int getSize(int t)
{
	if(S[t]) return S[t];
	if(!L[t] && !R[t]) S[t]=1;
	else if(!L[t]) S[t]=1+getSize(R[t]);
	else if(!R[t]) S[t]=1+getSize(L[t]);
	else S[t]=1+getSize(L[t])+getSize(R[t]);
	return S[t];
}

void colorred(int t)
{
	if(C[t]==1) return;
	C[t]=1;
	while(t!=0)
	{
		NR[t]++;
		t=F[t];
	}
}

void midorder(int t,int x)
{
	int s = getSize(t);
	int l = L[t]?getSize(L[t]):0;
	int r = R[t]?getSize(R[t]):0;
	x=x%s+1;
	if(x <= l) midorder(L[t],x-1);
	else if(x == l+1) colorred(t);
	else midorder(R[t],x-1-l-1);
}

int main()
{
	int N,P,Q;
	scanf("%d%d%d",&N,&P,&Q);
	for(int i = 1; i <= N; i++)
	{
		C[i]=0;NR[i]=0;F[i]=0;S[i]=0;
	}
	for(int i = 0; i < N; i++)
	{
		int x,Lx,Rx;
		scanf("%d%d%d",&x,&Lx,&Rx);
		L[x]=Lx;R[x]=Rx;F[Lx]=x;F[Rx]=x;
	}
	for(int i = 0; i < P; i++)
	{
		int t,x;
		scanf("%d%d",&t,&x);
		midorder(t,x);
	}
	for(int i = 0; i < Q; i++)
	{
		int w;
		scanf("%d",&w);
		printf("%d\n",NR[w]);
	}
	return 0;
}
