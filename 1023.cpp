#include <cstdio>

using namespace std;

void solvecase()
{
	int a,b;
	scanf("%d%d",&a,&b);
	if(b == 0)
	{
		int nums[600];
		for(int j = 0; j < a; j++)
		{
			for(int i = 0; i < a; i++)
				scanf("%d",&nums[i]);
			for(int i = 0; i < a; i++)
				printf("%d ",nums[a-i-1]);
			printf("\n");
		}
	}
	else if(b == 1)
	{
		int nums[600][600];
		for(int i = 0; i < a; i++)
			for(int j = 0; j < a; j++)
				scanf("%d",&nums[i][j]);
		for(int i = 0; i < a; i++)
		{
			for(int j = 0; j < a; j++)
				printf("%d ",nums[a-i-1][j]);
			printf("\n");
		}
	}
	else if(b == 2)
	{
		int nums[600][600];
		for(int i = 0; i < a; i++)
			for(int j = 0; j < a; j++)
				scanf("%d",&nums[i][j]);
		for(int i = 0; i < a; i++)
		{
			for(int j = 0; j < a; j++)
				printf("%d ",nums[j][i]);
			printf("\n");
		}
	}
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		solvecase();
	return 0;
}
