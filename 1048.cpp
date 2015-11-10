#include <cstdio>

using namespace std;

int main()
{
	int n;
	scanf("%d",&n);
	int L[1024],R[1024],F[1024];
	for(int i = 1; i <= n; i++)
		F[i] = 0;
	for(int i = 0; i < n/2; i++)
	{
		int A,B,C;
		scanf("%d%d%d",&A,&B,&C);
		L[A]=B;R[A]=C;F[B]=F[C]=A;
	}
	int root = 0;
	for(int i = 1; i <= n; i++)
		if(F[i] == 0) {root = i;break;}
	int Q[1024], p=0, q=0;
	Q[q++] = root;
	while(p<q)
	{
		printf("%d\n",Q[p]);
		if(q < n) Q[q++] = L[Q[p]];
		if(q < n) Q[q++] = R[Q[p]];
		p++;
	}
	return 0;
}
