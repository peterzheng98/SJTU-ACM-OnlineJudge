#include <cstdio>

using namespace std;

typedef long long Int;

int S,T;
int l[200001];
Int n[200001];

int len(int k)
{
	if(l[k] > 0) return l[k];
	int g[100], h = 0;
	for(int i = 0; i <= 99; i++)
		if((k*i)%100==0) g[h++]=i;
	l[k] = 1, n[k] = 1;
	int p = 1, q = 0;
	while(true)
	{
		q++;
		if(q >= h)
		{
			q = 0;
			p++;
		}
		int nb = k*p+k*g[q]/100;
		if(nb > T) break;

		int ll = len(nb)+1;
		if(ll > l[k])
		{
			l[k] = ll;
			n[k] = n[nb];
		}
		else if(ll == l[k])
			n[k]+=n[nb];
	}
	return l[k];
}

int main()
{
	scanf("%d%d",&S,&T);
	for(int i = S; i <= T; i++)
		l[i] = n[i] = -1;
	int m = 0;
	Int p = 0;
	for(int i = S; i <= T; i++)
		if(len(i)>m)
		{
			m = len(i);
			p = n[i];
		}
		else if(len(i)==m)
		{
			p += n[i];
		}
	printf("%d %lld\n",m,p);
	return 0;
}
