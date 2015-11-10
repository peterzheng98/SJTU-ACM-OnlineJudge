#include <cstdio>
#include <set>
#include <vector>

using namespace std;

typedef struct Box
{
	int size;
	int index;
	int treesize;
	int left;
	int right;
	int father;
	Box(){}
	Box(int i,int s=1):
	size(s),index(i),treesize(1),left(0),right(0),father(0){}
} Box;

bool operator<(const Box &b1, const Box &b2)
{
	if(b1.size > b2.size) return true;
	if(b1.size < b2.size) return false;
	return b1.index < b2.index;
}


bool operator>(const Box &b1, const Box &b2)
{
	if(b1.size < b2.size) return true;
	if(b1.size > b2.size) return false;
	return b1.index > b2.index;
}

typedef struct setLink
{
	int index;
	int size;
	setLink *next;
	setLink(){}
	setLink(int i):index(i),next(NULL),size(1){}
} setLink;

setLink *getBox(vector<setLink> &candies, int x)
{
	setLink *p = &candies[x];
	while(p->next) p=p->next;
	return p;
}

int main()
{
	int N,M;
	scanf("%d%d",&N,&M);
	set<Box> T;
	vector<setLink> candies(N+1);
	for(int i = 1; i <= N; i++)
	{
		candies[i] = setLink(i);
		T.insert(Box(i));
	}
	for(int i = 0; i < M; i++)
	{
		char c[2];
		scanf("%s",c);
		if(c[0] == 'C')
		{
			int x,y;
			scanf("%d%d",&x,&y);
			//printf("Combining %d and %d\n",x,y);
			setLink *a = getBox(candies,x);
			setLink *b = getBox(candies,y);
			if(a==b || a->size==0 || b->size==0)
			{
			//	printf("%p %d\n%p %d\n",a,a->size,b,b->size);
				continue;
			}
			T.erase(Box(a->index,a->size));
			T.erase(Box(b->index,b->size));
			T.insert(Box(a->index,a->size+b->size));
			b->next = a;
			a->size += b->size;
		}
		else if(c[0] == 'D')
		{
			int x;
			scanf("%d",&x);
			setLink *a = getBox(candies,x);
			if(a->size == 0) continue;
			T.erase(Box(a->index,a->size));
			a->size = 0;
		}
		else if(c[0] == 'Q')
		{
			int p;
			scanf("%d",&p);
			set<Box>::iterator iter = T.begin();
			for(int i = 0; i < p-1 && iter!=T.end(); i++,iter++)
				;
			if(iter != T.end())
				printf("%d\n",iter->size);
			else
				printf("0\n");
		}
	}
	return 0;
}
