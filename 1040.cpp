#include <iostream>

using namespace std;

typedef struct Node
{
	int data;
	Node* next;
	Node(int i):data(i),next(NULL){}
} Node;

int main()
{
	int N;
	cin >> N;
	int *L = new int[N];
	int *R = new int[N];
	for(int i = 0; i < N; i++) {L[i]=-1;R[i]=-1;}
	for(int i = 1; i < N; i++)
	{
		int f;
		cin >> f;
		if(L[f] == -1)
		{
			L[f] = i;
		}
		else
		{
			R[f] = i;
		}
	}
	Node head(0), *tail = new Node(0);
	head.next = tail;
	while(head.next!=NULL)
	{
		int d = head.next->data;
		cout << d << ' ';
		if(L[d] != -1) {tail->next=new Node(L[d]);tail=tail->next;}
		if(R[d] != -1) {tail->next=new Node(R[d]);tail=tail->next;}
		Node* p = head.next;
		head.next = p->next;
		delete p;
	}
	cout << endl;
	delete []L;
	delete []R;
	for(Node* p = head.next; p!=NULL; )
	{
		Node* q = p;
		p = p->next;
		delete q;
	}
	return 0;
}
