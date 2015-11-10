#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

typedef struct Pair{
	int h, n;
	Pair(){}
	Pair(int H, int N):h(H),n(N){}
} Pair;

bool operator<(Pair p1, Pair p2)
{
	if(p1.h < p2.h) return true;
	if(p1.h > p2.h) return false;
	return p1.n < p2.n;
}

int main()
{
	int N;
	set<Pair> S;
	scanf("%d",&N);
	int f[100001];
	for(int i = 1; i <= N; i++)
	{
		int h;
		scanf("%d",&h);
		f[i] = h;
		S.insert(Pair(h,i));
	}
	char cmd[20];
	while(true)
	{
		if(scanf("%s",cmd) < 1) break;
		if(strcmp(cmd,"findmin") == 0)
		{
			int x;
			scanf("%d",&x);
			set<Pair>::iterator iter = S.upper_bound(Pair(x,N+1));
			printf("%d\n",iter->n);
		}
		if(strcmp(cmd,"decrease") == 0)
		{
			int i,j;
			scanf("%d%d",&i,&j);
			S.erase(Pair(f[i],i));
			f[i] -= j;
			S.insert(Pair(f[i],i));
		}
	}
	return 0;
}
