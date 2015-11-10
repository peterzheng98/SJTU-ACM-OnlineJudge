#include <cstdio>

using namespace std;

int main()
{
	int N;
	scanf("%d",&N);
	int pos[1000000];
	bool in[1000000];
	for(int i = 0; i < N; i++)
		in[i] = false;
	in[0] = true;
	bool ans = true;
	for(int i = 1; i < N; i++)
	{
		if(!ans) continue;
		int n;
		scanf("%d",&n);
		int p = pos[n];
		if(!in[2*p+1])
		{
			if(2*p+1 >= N) ans=false;
			else
			{
				in[2*p+1] = true;
				pos[i] = 2*p+1;
			}
		}
		else if(!in[2*p+2])
		{
			if(2*p+2 >= N) ans=false;
			else
			{
				in[2*p+2] = true;
				pos[i] = 2*p+2;
			}
		}
		else ans = false;
	}
	if(ans) printf("true\n");
	else printf("false\n");
	return 0;
}
