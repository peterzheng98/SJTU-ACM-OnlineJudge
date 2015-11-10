#include <cstdio>
#include <set>

using namespace std;

typedef struct Interval {
	int left, length;
	Interval() {}
	Interval(int l, int r):left(l),length(r-l){}
	int l()const {return left;}
	int r()const {return left+length;}
	int len()const {return length;}
} Interval;

bool operator<(Interval i1, Interval i2)
{
	if(i1.l() < i2.l()) return true;
	if(i1.l() > i2.l()) return false;
	return i1.r() < i2.r();
}

bool operator>(Interval i1, Interval i2)
{
	if(i1.l() > i2.l()) return true;
	if(i1.l() < i2.l()) return false;
	return i1.r() > i2.r();
}

bool operator==(Interval i1, Interval i2)
{
	return i1.l() == i2.l() && i1.r() == i2.r();
}

set<Interval> invs;

void insert(int l, int r)
{
	if(l >= r) return;
	Interval inv(l,r);
	if(invs.empty())
	{
		invs.insert(inv);
		return;
	}
	Interval right(r+1,0);
	set<Interval>::iterator iter = invs.upper_bound(right);
	if(iter == invs.begin())
	{
		invs.insert(inv);
		return;
	}
	else
	{
		iter--;
		while( iter != invs.end() && iter->r() >= l )
		{
			if(iter->r() >= r) {r = iter->r(); inv = Interval(l,r);}
			if(iter->l() <= l) {l = iter->l(); inv = Interval(l,r);}
			invs.erase(iter);
			iter--;
		}
	}
	invs.insert(inv);
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		insert(a,b);
	}
	int sum = 0;
	for(set<Interval>::iterator iter = invs.begin(); iter != invs.end(); iter++)
		sum += iter->len();
	printf("%d\n",sum);
	return 0;
}
