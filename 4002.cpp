#include <cstdio>

using namespace std;

int main()
{
	int M[50][50];
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			scanf("%d",&M[i][j]);
	int S[50][50];
	S[0][0] = 1;
	for(int i = 0; i < n; i++)
		S[i][0] = 1;
	for(int j = 0; j < m; j++)
		S[0][j] = 1;
	int max = 1;
	for(int i = 1; i < n; i++)
		for(int j = 1; j < m; j++)
		{
			int k = i>j?j:i;
			for(int l = 0; l <= k; l++)
			{
				if(M[i-l][j] == M[i][j] &&
				   M[i-l][j-l] == M[i][j] &&
				   M[i][j-l] == M[i][j])
				    S[i][j] = l+1;
			}
			if(S[i][j] > max) max = S[i][j];
		}
	printf("%d\n",max*max);
	return 0;
}
