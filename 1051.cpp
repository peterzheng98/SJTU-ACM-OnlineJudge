#include <iostream>

using namespace std;

typedef long Int;

typedef struct Node
{
	Int d;
	Node* prev;
	Node* next;
	Node(Int m) :d(m) {}
} Node;

class List
{
public:
	List()
	:ncomp(0)
	{
		head = new Node(0);
		tail = new Node(0);
		head->prev = NULL;
		head->next = tail;
		tail->prev = head;
		tail->next = NULL;
	}

	~List()
	{
		Node *p = head;
		while(p)
		{
			Node *q = p;
			p = p->next;
			delete q;
		}
	}

	void insertToHead(Int d)
	{
		Node *node = new Node(d);
		node->prev = head;
		node->next = head->next;
		head->next->prev = node;
		head->next = node;
	}

	void insertToHead(Node* node)
	{
		node->prev = head;
		node->next = head->next;
		head->next->prev = node;
		head->next = node;
	}

	void insertToTail(Int d)
	{
		Node *node = new Node(d);
		node->prev = tail->prev;
		node->next = tail;
		tail->prev->next = node;
		tail->prev = node;
	}

	Node* search(Int d)
	{
		Node* p = head->next;
		while(p!=tail)
		{
			ncomp ++;
			if(p->d == d) return p;
			p = p->next;
		}
		return NULL;
	}

	void del(Node* p)
	{
		if(p == NULL) return;
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
	}

	void moveToHead(Node *p)
	{
		if(p == NULL) return;
		p->prev->next = p->next;
		p->next->prev = p->prev;
		insertToHead(p);
	}

	void print()
	{
		Node *p = head->next;
		while(p->next != NULL)
		{
			cout << p->d;
			p = p->next;
		}
	}

	Node *head;
	Node *tail;
	Int ncomp;
};

int main()
{
	int n;
	cin >> n;
	List l;
	for(int i = 0; i < n; i++)
	{
		int k;
		cin >> k;
		l.insertToTail(k);
	}
	int m;
	cin >> m;
	for(int i = 0; i < m; i++)
	{
		int k;
		cin >> k;
		Node* p = l.search(k);
		l.moveToHead(p);
	}
	cout << l.ncomp << endl;
	return 0;
}
