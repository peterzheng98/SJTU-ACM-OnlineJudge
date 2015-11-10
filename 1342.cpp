#include <cstdio>

using namespace std;

typedef struct Node
{
	int name;
	Node* next;
	Node* prev;
	Node():name(0),next(NULL),prev(NULL){}
	Node(int t):name(t),next(NULL),prev(NULL){}
} Node;

int main()
{
	int test;
	scanf("%d",&test);
	for(int t = 0; t < test; t++)
	{
		char names[50000][21] = {"Empty!"};
		int nn=1;
		Node dgs[10001];
		Node* ps[10001];
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i = 1; i <= n; i++)
			ps[i] = &dgs[i];
		printf("Case %d:\n",t+1);
		for(int i = 0; i < m; i++)
		{
			char cmd[5];
			scanf("%s",cmd);
			if(cmd[0]=='p' && cmd[1]=='u' && cmd[2]=='s')
			{
				int k;
				int name;
				scanf("%d",&k);
				ps[k]->next = new Node(nn);
				ps[k]->next->prev = ps[k];
				ps[k]=ps[k]->next;
				scanf("%s",names[nn++]);
			}
			else if(cmd[0]=='p' && cmd[1]=='o')
			{
				int k;
				scanf("%d",&k);
				if(ps[k]->prev!=NULL)
				{
					ps[k]=ps[k]->prev;
					delete ps[k]->next;
					ps[k]->next = NULL;
				}
			}
			else if(cmd[0]=='p' && cmd[1]=='u' && cmd[2]=='t')
			{
				int l,k;
				scanf("%d%d",&l,&k);
				if(l==k) continue;
				ps[l]->next=dgs[k].next;
				if(ps[l]->next)
				{
					ps[l]->next->prev=ps[l];
					ps[l]=ps[k];
				}
				dgs[k].next=NULL;
				ps[k]=&dgs[k];
			}
			else if(cmd[0]=='t')
			{
				int k;
				scanf("%d",&k);
				printf("%s\n",names[ps[k]->name]);
			}
		}
		for(int i = 1; i <= n; i++)
		{
			Node* p = dgs[i].next;
			while(p)
			{
				Node* q = p;
				p = p->next;
				delete q;
			}
		}
	}
	return 0;
}
