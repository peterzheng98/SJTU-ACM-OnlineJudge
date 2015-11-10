#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct Node
{
	int i;
	Node* next;
	Node(int t):i(t),next(NULL){}
} Node;

int main()
{
	int M;
	cin >> M;
	Node* p = new Node(1);
	Node* q = p;
	for(int i = 0; i < M-1; i++)
	{
		Node* n = new Node(i+2);
		q->next = n;
		q = q->next;
	}
	q -> next = p;

	for(int i = 0; i < M-1; i++)
	{
		int k;
		cin >> k;
		k %= (M-i);
		Node* r = NULL;
		if(k == 0) k+=(M-i);
		for(int j = 0; j < k; j++)
		{
			r = q;
			q = q->next;
		}
		r->next = q->next;
		delete q;
		q=r;
	}

	cout << q->i << endl;

	delete q;

	return 0;
}
