#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long int Int;

typedef struct Edge {
	int w,u,v;
	Edge(){}
	Edge(int a,int b,int c):w(a),u(b),v(c){}
} Edge;

bool operator<(Edge e1, Edge e2)
{
	return e1.w < e2.w;
}

int findroot(int *S, int k)
{
	if(S[k] == -1) return k;
	return S[k] = findroot(S,S[k]);
}

int size(int *S, int *N, int k)
{
	return N[findroot(S,k)];
}

void combine(int *S, int *N, int u, int v)
{
	int r1 = findroot(S,u);
	int r2 = findroot(S,v);
	if(r1 != r2)
	{
		N[r2] += N[r1];
		S[r1] = r2;
	}
}

void testcase(int test)
{
	int n;
	Edge edges[15000];
	int S[15001];
	int N[15001];
	scanf("%d",&n);
	for(int i = 0; i < n-1; i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		edges[i] = Edge(w,u,v);
	}
	for(int i = 1; i <= n; i++)
	{
		S[i] = -1;
		N[i] = 1;
	}
	sort(edges,edges+n-1);
	Int W = 0;
	for(int i = 0; i < n-1; i++)
	{
		Int u = edges[i].u, v = edges[i].v, w = edges[i].w;
		Int p = size(S,N,u), q = size(S,N,v);
		W += w+(p*q-1)*(w+1);
		combine(S,N,u,v);
	}
	printf("%lld\n",W);
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int i = 1; i <= t; i++)
		testcase(i);
	return 0;
}
