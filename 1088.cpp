#include <cstdio>
#include <map>

using namespace std;
int a[16][16];

typedef struct Pair
{
	int S,c;
	Pair(int a,int b):S(a),c(b){}
} Pair;

bool operator<(Pair a, Pair b)
{
	if(a.S < b.S) return true;
	if(a.S > b.S) return false;
	return a.c < b.c;
}

map<Pair,int> DD;

bool in(int S, int c)
{
	return (S >> (c-1))%2;
}

int erase(int S, int c)
{
	S &= (~(1 << (c-1)));
	return S;
}

int D(int S, int c, int N)
{
	if(DD.find(Pair(S,c)) != DD.end())
		return DD[Pair(S,c)];
	int min = -1;
	S = erase(S,c);
	for(int i = 1; i <= N; i++)
	{
		if(in(S,i))
		{
			int m = D(S,i,N) + a[i][c];
			if(min == -1 || m < min) min = m;
		}
	}
	DD[Pair(S,c)] = min;
	return min;
}

int TSP(int s, int N)
{
	int S = (int)(((unsigned int)(-1))>>(32-N));
	S = erase(S,s);
	DD.clear();
	for(int i = 1; i <= N; i++)
	{
		if(in(S,i))
		{
			DD[Pair(1<<(i-1),i)] = a[s][i];
		}
	}
	int min = -1;
	for(int i = 1; i <= N; i++)
	{
		if(in(S,i))
		{
			int m = D(S,i,N) + a[i][s];
			if(min == -1 || m < min) min = m;
		}
	}
	return min;
}

int main()
{
	int N;
	scanf("%d",&N);
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			scanf("%d",&a[i][j]);
	if(N == 1)
		printf("0\n");
	else if(N==2)
		printf("%d\n",2*a[1][2]);
	else
		printf("%d\n",TSP(1,N));
	return 0;
}
