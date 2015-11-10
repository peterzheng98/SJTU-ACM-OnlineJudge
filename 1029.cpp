#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct Node
{
	int d;
	Node* next;
	Node(int a):d(a),next(NULL){}
} Node;

int main()
{
	int n;
	cin >> n;
	Node* ss[100];
	Node* ts[100];
	char c;
	while((c=cin.get())<'0' || c>'9')
		;
	cin.putback(c);
	for(int i = 0; i < n; i++) ss[i] = NULL;
	for(int i = 0; ; )
	{
		if(ss[i] == NULL)
		{
			ss[i] = new Node(0);
			ts[i] = ss[i];
		}
		int k;
		cin >> k;
		ts[i]->next = new Node(k);
		ts[i] = ts[i]->next;
		while((c=cin.get())<'0' || c>'9')
		{
			if(c == '\n') i++;
			if(i >= n) break;
		}
		if(i >= n) break;
		if(c != '\n') cin.putback(c);
	}

	for(int i = 0; i < n-1; i++)
	{
		int x,y;
		cin >> x >> y;
		ts[y-1]->next = ss[x-1]->next;
		ts[y-1] = ts[x-1];
		ss[x-1]->next = NULL;
		ts[x-1] = ss[x-1];
	}

	for(int i = 0; i < n; i++)
	{
		if(ss[i]->next)
		{
			Node* p = ss[i] -> next;
			while(p)
			{
				cout << p->d << ' ';
				p = p->next;
			}
			cout << endl;
		}
	}

	for(int i = 0; i < n; i++)
	{
		Node* p = ss[i];
		while(p)
		{
			Node* q = p;
			p = p->next;
			delete q;
		}
	}
	return 0;
}
