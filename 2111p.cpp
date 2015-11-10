#include <cstdio>
#include <cmath>
#include <set>

using namespace std;

int main()
{
	set<int> S;
	int M;
	scanf("%d",&M);
	for(int i = 0; i < M; i++)
	{
		int o,x;
		scanf("%d%d",&o,&x);
		switch(o)
		{
		case 0:
		{
			set<int>::iterator iter;
			iter = S.end(); iter--;
			if(x >= *iter)
				printf("%d\n",x-*iter);
			else if(x <= *S.begin())
				printf("%d\n",*S.begin()-x);
			else
			{
				int l=-1,r=-1;
				iter = S.lower_bound(x);
				if(iter!=S.end()) l=abs(*iter-x);
				iter = S.upper_bound(x);
				if(iter!=S.end()) {iter--;r=abs(*iter-x);}
				if(l==-1 || (r>=0 && r<l)) printf("%d\n",r);
				else printf("%d\n",l);
			}
			break;
		}
		case 1:
			S.insert(x);
			break;
		case 2:
			S.erase(x);
		}
	}
	return 0;
}
