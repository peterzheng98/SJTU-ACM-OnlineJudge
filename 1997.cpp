#include <cstdio>
#include <cmath>

using namespace std;

int main()
{
	int N,W;
	scanf("%d%d",&N,&W);
	int min = -1, wt = -1;
	for(int i = 0; i < N; i++)
	{
		int w;
		scanf("%d",&w);
		if(min == -1 || abs(w-W)<min || (abs(w-W)==min && w>wt))
		{
			min = abs(w-W);
			wt = w;
		}
	}
	printf("%d\n",wt);
	return 0;
}
