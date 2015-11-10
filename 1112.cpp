#include <cstdio>
#include <set>

using namespace std;

int main()
{
	int n,k;
	int S[1001];
	bool v[1001];
	set<int> s;
	int t[100001];
	bool r[1001][1001];
	scanf("%d%d",&n,&k);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d",&S[i]);
		t[S[i]] = i;
		v[i] = false;
	}
	for(int i = 0; i < k; i++)
	{
		int j;
		scanf("%d",&j);
		s.insert(-S[j]);
		v[j] = true;
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
		{
			int m;
			scanf("%d",&m);
			r[i][j] = m==1;
		}
	while(!s.empty())
	{
		int f = -*s.begin();
		int j = t[f];
		printf("%d\n",j);
		s.erase(-f);
		for(int i = 1; i <= n; i++)
			if(r[i][j] && !v[i])
			{
				s.insert(-S[i]);
				v[i] = true;
			}
	}
	return 0;
}
