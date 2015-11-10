#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <set>

using namespace std;

char buf[5000000];

typedef struct Node
{
	int k;
	set<int> c;
	Node():k(0){}
} Node;

Node nodes[100001];

int next(int p)
{
	register int t=p;
	do ++t;
	while(buf[t]==' ');
	return t;
}

int heap[100000];
int stack[100000];
int h=0;
int s=0;

void push(int k)
{
	stack[s++]=k;
}

int pop()
{
	if(s==0) return 0;
	return stack[--s];
}

void heappush(int k)
{
	heap[h++] = k;
	int r = h-1;
	while(r>0)
	{
		int rr = (r-1)/2;
		int a = heap[rr];
		int b = heap[r];
		if(a<=b) break;
		int tmp=heap[rr];
		heap[rr]=heap[r];
		heap[r]=tmp;
		r=rr;
	}
}

int heappop()
{
	if(h==0) return 0;
	int ans = heap[0];
	heap[0] = heap[--h];
	int r=0;
	while(2*r+1 < h)
	{
		int rr=2*r+1, rrr=2*r+2;
		if(rrr<h && heap[rrr] < heap[rr])
			rr = rrr;
		if(heap[r] <= heap[rr]) break;
		int tmp=heap[rr];
		heap[rr]=heap[r];
		heap[r]=tmp;
		r=rr;
	}
	return ans;
}

int main()
{
	cin.getline(buf,1000000);
	register int q = 0;
	for(int p=0;buf[p];p=next(p))
	{
		char c=buf[p];
		if(c=='(')
		{
			p=next(p);
			register int k = atoi(buf+p);
			if(q)
			{
				nodes[q].c.insert(k);
				nodes[k].c.insert(q);
				push(q);
			}
			q = k;
		}
		else if(c==')')
		{
			if(nodes[q].c.size()==1) heappush(q);
			q = pop();
		}
	}
	if(nodes[q].c.size()==1) heappush(q);
	while(h>1)
	{
		int l = heappop();
		int m = *nodes[l].c.begin();
		set<int>& v = nodes[m].c;
		v.erase(l);
		if(v.size()==1) heappush(m);
		printf("%d ",m);
	}
	printf("\n");
	return 0;
}
