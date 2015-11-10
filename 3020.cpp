#include <cstdio>

using namespace std;

void heappush(long long buf[], long long &s, long long e)
{
	buf[s++] = e;
	long long p = s-1;
	while(p > 0)
	{
		long long q = (p-1)/2;
		if(buf[q] > buf[p])
		{
			long long tmp = buf[q];
			buf[q] = buf[p];
			buf[p] = tmp;
			p = q;
		}
		else break;
	}
}

long long heappop(long long buf[], long long &s)
{
	if(s <= 0) return 0;
	long long ans = buf[0];
	buf[0] = buf[--s];
	long long p = 0;
	while(2*p+1<s)
	{
		long long q = 2*p+1, qq = 2*p+2;
		if(buf[p] < buf[q])
		{
			if(qq >= s || buf[p] <= buf[qq])
				break;
			else
			{
				long long tmp = buf[p];
				buf[p] = buf[qq];
				buf[qq] = tmp;
				p = qq;
			}
		}
		else
		{
			if(qq >= s || buf[q] <= buf[qq])
			{
				long long tmp = buf[p];
				buf[p] = buf[q];
				buf[q] = tmp;
				p = q;
			}
			else
			{
				long long tmp = buf[p];
				buf[p] = buf[qq];
				buf[qq] = tmp;
				p = qq;
			}
		}
	}
	return ans;
}

int main()
{
	long long buf[200000];
	long long N,M;
	scanf("%lld%lld",&N,&M);
	long long p = 0, s = 0;
	long long k = M-2-(N-2)%(M-1);
	for(long long i = 0; i < k; i++)
		heappush(buf,s,0);
	for(long long i = 0; i < N; i++)
	{
		scanf("%lld",&p);
		heappush(buf,s,p);
	}
	long long res = 0;
	while(s > 1)
	{
		long long sum = 0;
		for(long long i = 0; i < M; i++)
		{
			long long r = heappop(buf,s);
			res += r;
			sum += r;
		}
		heappush(buf,s,sum);
	}
	printf("%lld\n",res);
	return 0;
}
