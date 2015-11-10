#include <iostream>
#include <string>

using namespace std;

template<typename T>
struct Node
{
	T data;
	Node* prev;
	Node* next;
	Node(T t) :data(t) {}
};

template<typename T>
class List
{
public:
	List()
	{
		head = new Node<T>(0);
		tail = new Node<T>(0);
		head->prev = NULL;
		head->next = tail;
		tail->prev = head;
		tail->next = NULL;
	}

	~List()
	{
		struct Node<T> *p = head;
		while(p)
		{
			struct Node<T> *q = p;
			p = p->next;
			delete q;
		}
	}

	void insertToHead(T d)
	{
		struct Node<T> *node = new struct Node<T>(d);
		node->prev = head;
		node->next = head->next;
		head->next->prev = node;
		head->next = node;
	}

	void insertToTail(T d)
	{
		struct Node<T> *node = new struct Node<T>(d);
		node->prev = tail->prev;
		node->next = tail;
		tail->prev->next = node;
		tail->prev = node;
	}

	void print()
	{
		struct Node<T> *p = head->next;
		while(p->next != NULL)
		{
			cout << p->data;
			p = p->next;
			if(p->next != NULL) cout << ' ';
		}
	}

	List<T> operator+(const List<T>& rh) const
	{
		List<T> r;
		struct Node<T> *p = head->next;
		while(p != tail)
		{
			r.insertToTail(p->data);
			p = p->next;
		}
		p = rh.head->next;
		while(p != rh.tail)
		{
			r.insertToTail(p->data);
			p = p->next;
		}
		return r;
	}

	struct Node<T> *head;
	struct Node<T> *tail;
};

template<typename T>
void solve(int n, int m)
{
	List<T> l, r;
	for(int i = 0; i < n; i++)
	{
		T t;
		cin >> t;
		l.insertToTail(t);
	}
	for(int i = 0; i < m; i++)
	{
		T t;
		cin >> t;
		r.insertToTail(t);
	}
	List<T> s = l+r;
	s.print();
}

int main()
{
	string type;
	cin >> type;
	int n,m;
	cin >> n >> m;
	if(type == "int")
		solve<int>(n,m);
	else if(type == "char")
		solve<char>(n,m);
	else if(type == "double")
		solve<double>(n,m);
	return 0;
}
