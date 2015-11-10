#include <cstdio>

using namespace std;

typedef struct Node {
	int idx;
	Node *child;
	Node *sibling;
	Node *father;
	bool alive;
	Node():idx(0),child(NULL),sibling(NULL),father(NULL),alive(true){}
	Node(int i, Node *f):idx(i),child(NULL),sibling(NULL),father(f),alive(true){}
} Node;

int main()
{
	Node nodes[200001];
	int N;
	scanf("%d",&N);
	nodes[1] = Node(1,NULL);
	int num = 1;
	for(int i = 0; i < N; i++)
	{
		char c[2];
		scanf("%s",c);
		if(c[0]=='B')
		{
			int x,y;
			scanf("%d%d",&x,&y);
			Node **p = &(nodes[x].child);
			while(*p) p=&((*p)->sibling);
			nodes[y] = Node(y,&nodes[x]);
			*p = &nodes[y];
		}
		else if(c[0]=='D')
		{
			int x;
			scanf("%d",&x);
			num--;
			if(nodes[x].father) num++;
			Node *p = nodes[x].child;
			while(p)
			{
				if(p->alive) num++;
				p->father = NULL;
				p = p->sibling;
			}
			nodes[x].alive = false;
			printf("%d\n",num);
		}
	}
	return 0;
}
