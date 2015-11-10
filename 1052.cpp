#include <cstdio>
#include <set>

using namespace std;

int main()
{
	int N;
	scanf("%d",&N);
	set<int> S[101];
	int n[101];
	for(int i = 1; i <= N; i++)
		scanf("%d",&n[i]);
	for(int i = 1; i <= N; i++)
	{
		for(int j = 0; j < n[i]; j++)
		{
			int b;
			scanf("%d",&b);
			S[i].insert(b);
		}
	}
	int M;
	scanf("%d",&M);
	for(int i = 0; i < M; i++)
	{
		char cmd[2];
		int A,B;
		scanf("%s%d%d",cmd,&A,&B);
		if(cmd[0] == '+')
		{
			for(set<int>::iterator iter = S[B].begin(); iter!=S[B].end(); iter++)
				S[A].insert(*iter);
		}
		else if(cmd[0] == '-')
		{
			for(set<int>::iterator iter = S[B].begin(); iter!=S[B].end(); iter++)
			{
				if(S[A].find(*iter)!=S[A].end())
					S[A].erase(*iter);
			}
		}
		else if(cmd[0] == '*')
		{
			set<int> s;
			for(set<int>::iterator iter = S[B].begin(); iter!=S[B].end(); iter++)
				if(S[A].find(*iter)!=S[A].end())
					s.insert(*iter);
			S[A] = s;
		}
	}
	for(int i = 1; i <= N; i++)
	{
		for(set<int>::iterator iter = S[i].begin(); iter!=S[i].end(); iter++)
			printf("%d ",*iter);
		printf("\n");
	}
	return 0;
}
