#include <cstdio>
#include <set>

using namespace std;

typedef struct Pair{
	int v,w;
	Pair(int V,int W):v(V),w(W){}
} Pair;

bool operator<(Pair p1, Pair p2)
{
	return p1.w < p2.w;
}


void solvecase(int casenum)
{
	printf("Case #%d:\n",casenum);
	int n,m,Q;
	set<Pair> V[100001];
	int D[100001];
	bool T[100001];
	int prevT = -1;
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i++)
	{
		int t;
		scanf("%d",&t);
		T[i]=t==1;
	}
	for(int i = 0; i < m; i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(T[a] && T[b]) continue;
		V[a].insert(Pair(b,c));
		V[b].insert(Pair(a,c));
	}
	for(int i = 1; i <= n; i++)
	{
		D[i] = -1;
		if(T[i])
		{
			if(prevT == -1)
			{
				prevT = i;
			}
			else
			{
				V[i].insert(Pair(prevT,0));
				V[prevT].insert(Pair(i,0));
				prevT = i;
			}
		}
	}
	D[1] = 0;
	set<Pair> ps;
	ps.insert(Pair(1,0));
	while(!ps.empty())
	{
		Pair p = *ps.begin();
		set<Pair>& l = V[p.v];
		ps.erase(p);
		for(set<Pair>::iterator iter = l.begin(); iter!=l.end(); iter++)
		{
			if(D[iter->v]==-1)
			{
				D[iter->v] = p.w+iter->w;
				ps.insert(Pair(iter->v,D[iter->v]));
			}
			else if(p.w+iter->w < D[iter->v])
			{
				ps.erase(Pair(iter->v,D[iter->v]));
				D[iter->v] = p.w+iter->w;
				ps.insert(Pair(iter->v,D[iter->v]));
			}
		}
	}
	scanf("%d",&Q);
	for(int i = 0; i < Q; i++)
	{
		int C;
		scanf("%d",&C);
		printf("%d\n",D[C]);
	}
}

int main()
{
	int T;
	scanf("%d",&T);
	for(int i = 1; i <= T; i++)
		solvecase(i);
	return 0;
}
