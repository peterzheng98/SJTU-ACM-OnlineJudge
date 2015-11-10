#include <cstdio>
#include <cmath>
#include <set>
#include <map>

using namespace std;


int gcd(int a,int b)
{
	if(a==0) return b;
	if(b==0) return a;
	a%=b; return abs(gcd(b,a));
}

typedef struct Q
{
	int a,b;
	Q(int m,int n):a(m),b(n)
	{
		if(b==0) a=(a==0?0:1);
		else if(a==0) b=1;
		else
		{
			int d = gcd(a,b);
			a/=d;b/=d;
			if(b<0){a=-a;b=-b;}
		}
	}
} Q;

const Q Inf = Q(1,0);

bool operator<(Q q1, Q q2)
{
	if(q1.a<q2.a) return true;
	if(q1.a>q2.a) return false;
	return q1.b<q2.b;
}

bool operator>(Q q1, Q q2)
{
	if(q1.a>q2.a) return true;
	if(q1.a<q2.a) return false;
	return q1.b>q2.b;
}

bool operator==(Q q1, Q q2)
{
	return q1.a==q2.a && q1.b==q2.b;
}

typedef struct L
{
	Q s,d;
	int x;
} L;

bool operator<(L l1, L l2)
{
	if(l1.s<l2.s) return true;
	if(l1.s>l2.s) return false;
	if(l1.d<l2.d) return true;
	if(l1.d>l2.d) return false;
	return l1.x<l2.x;
}

bool operator>(L l1, L l2)
{
	if(l1.s>l2.s) return true;
	if(l1.s<l2.s) return false;
	if(l1.d>l2.d) return true;
	if(l1.d<l2.d) return false;
	return l1.x>l2.x;
}

bool operator==(L l1, L l2)
{
	return l1.d==l2.d && l1.s==l2.s && l1.x==l2.x;
}

L getline(int x1, int y1, int x2, int y2)
{
	int dx = x2-x1, dy = y2-y1;
	Q s = Q(dy,dx), d = Q(x1*y2-x2*y1,x1-x2);
	if(s==Inf)
	{
		L l = {s,d,x1};
		return l;
	}
	else
	{
		L l = {s,d,0};
		return l;
	}
}

void printline(L l)
{
	printf("%d %d %d %d %d\n",l.s.a,l.s.b,l.d.a,l.d.b,l.x);
}

typedef map<L,int> Lines;
typedef set<L> Flag;

int main()
{
	int N;
	scanf("%d",&N);
	int xs[700],ys[700];
	Lines ls;
	Flag flag;
	int max = 0;
	for(int k = 0; k < N; k++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		xs[k] = x; ys[k] = y;
		flag.clear();
		for(int i = 0; i < k; i++)
		{
			L l = getline(xs[i],ys[i],xs[k],ys[k]);
			if(flag.find(l) == flag.end())
			{
				ls[l]++;
				int tmp = ls[l];
				if(tmp > max) max = tmp;
				flag.insert(l);
			}
		}
		#if 0
		printf("Modified: \n");
		for(Flag::iterator iter=flag.begin(); iter!=flag.end(); iter++)
			printline(*iter);
		printf("----\n");
		#endif
	}
	#if 0
	for(Lines::iterator iter=ls.begin();iter!=ls.end();iter++)
	{
		printline(iter->first);
		printf("%d\n",iter->second);
	}
	#endif
	printf("%d\n",max+1);
	return 0;
}
