#include <cstdio>
#include <set>

using namespace std;

typedef struct Pair{
	int i,j;
	Pair(int a,int b):i(a),j(b){}
} Pair;

bool operator<(Pair p1, Pair p2)
{
	if(p1.i < p2.i) return true;
	if(p1.i > p2.i) return false;
	return p1.j < p2.j;
}

set<Pair> ps;

void _DFS(bool m[500][500], int i, int j, int N, int M)
{
	m[i][j] = false;
	ps.erase(Pair(i,j));
	if(i > 0 && m[i-1][j]) _DFS(m,i-1,j,N,M);
	if(i < N-1 && m[i+1][j]) _DFS(m,i+1,j,N,M);
	if(j > 0 && m[i][j-1]) _DFS(m,i,j-1,N,M);
	if(j < M-1 && m[i][j+1]) _DFS(m,i,j+1,N,M);
}

int DFS(bool m[500][500], int N, int M)
{
	ps.clear();
	for(int i = 0; i < N; i++)
		for(int j = 0; j < M; j++)
			if(m[i][j]) ps.insert(Pair(i,j));
	int count = 0;
	while(!ps.empty())
	{
		Pair p = *ps.begin();
		_DFS(m,p.i,p.j,N,M);
		count++;
	}
	return count;
}

int main()
{
	int N, M;
	bool m[500][500];
	scanf("%d%d",&N,&M);
	for(int i = 0; i < N; i++)
		for(int j = 0; j < M; j++)
		{
			int k;
			scanf("%d",&k);
			m[i][j] = k==0;
		}
	int l = DFS(m,N,M);
	printf("%d\n",l);
	return 0;
}
