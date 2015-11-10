#include <cstdio>
#include <set>

using namespace std;

typedef struct Seg
{
	int l,r;
	Seg(int a,int b):l(a),r(b){}
} Seg;

bool operator<(Seg s1, Seg s2)
{
	return s1.l < s2.l;
}

int main()
{
	int N;
	scanf("%d",&N);
	set<Seg> s;
	for(int i = 0; i < N; i++)
	{
		int a,b,l,r;
		scanf("%d%d",&a,&b);
		if(a>=b) continue;
		set<Seg>::iterator iter1 = s.lower_bound(Seg(a,b));
		if(iter1==s.end())
		{
			iter1=s.begin();
			l=a;
		}
		else
		{
			if(iter1->r < a) {iter1++;l=a;}
			else l=iter1->l;
		}
		set<Seg>::iterator iter2 = s.upper_bound(Seg(b,b));
		if(iter2==s.end())
		{
			r=b;
		}
		else
		{
			if(iter2==s.begin())
				r=b;
			else
			{
				iter2--;
				if(iter2->r <= b) r=b;
				else r=iter2->r;
				iter2++;
			}
		}
		printf("Bound Segments: %d,%d-%d,%d\n",iter1->l,iter1->r,iter2->l,iter2->r);
		printf("Original Segment: %d,%d\n",a,b);
		printf("New Segment: %d,%d\n",l,r);
		s.erase(iter1,iter2);
		s.insert(Seg(l,r));
		printf("Segments:\n");
		for(set<Seg>::iterator iter=s.begin(); iter!=s.end(); iter++)
		{
			printf("[%d,%d]\n",iter->l,iter->r);
		}
	}
	unsigned int len=0;
	for(set<Seg>::iterator iter=s.begin(); iter!=s.end(); iter++)
	{
		len += (iter->r-iter->l);
	}
	printf("%u\n",len);
	return 0;
}
