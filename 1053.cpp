#include <iostream>
#include <cstdio>
#include <algorithm>
 
using namespace std;
 
typedef struct Pair
{
	int y;
	int d;
	Pair():y(0),d(0){}
	Pair(int a,int b):y(a),d(b){}
} Pair;
 
bool operator<(Pair a1, Pair a2)
{
	return a1.y < a2.y;
}
 
bool operator==(Pair a1, Pair a2)
{
	return a1.y == a2.y;
}
 
Pair* find(Pair* l, Pair* r, Pair p)
{
	for(Pair* i = l; i < r; i++)
		if(i->y == p.y) return i;
	return NULL;
}
 
class Vector
{
public:
	Vector()
	{
		capacity = 2;
		data = new Pair[capacity];
		length = 0;
	}
 
	~Vector()
	{
		delete []data;
	}
 
	void doubleSpace()
	{
		Pair* tmp = new Pair[capacity*2];
		capacity *= 2;
		for(register int i = 0; i < length; i++)
			tmp[i] = data[i];
		delete []data;
		data = tmp;
	}
 
	void insert(Pair d)
	{
		if(length >= capacity)
			doubleSpace();
		data[length++] = d;
	}
 
	void ssort()
	{
		sort(data,data+length);
	}
 
	int at(int y)
	{
		Pair p(y,0);
		Pair* q = find(data,data+length,p);
		if(q == NULL) return 0;
		return q->d;
	}
 
	Pair* data;
	int capacity;
	int length;
}; 
 
int main()
{
	int n;
	cin >> n;
	Vector matrix[100000];
	int xindex[100000];
	int yindex[100000];
	for(register int i = 0; i < 100000; i++)
		xindex[i] = yindex[i] = i;
	for(register int i = 0; i < n; i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		matrix[x].insert(Pair(y,z));
	}
	// for(register int i = 0; i < 100000; i++)
	//	matrix[i].ssort();
 
	int m;
	cin >> m;
	for(register int i = 0; i < m; i++)
	{
		int op, x, y;
		scanf("%d%d%d",&op,&x,&y);
		if(op == 0)
		{
			int tmp = xindex[x];
			xindex[x] = xindex[y];
			xindex[y] = tmp;
		}
		else if(op == 1)
		{
			int tmp = yindex[x];
			yindex[x] = yindex[y];
			yindex[y] = tmp;
		}
		else if(op == 2)
		{
			int xx = xindex[x];
			int yy = yindex[y];
			printf("%d\n",matrix[xx].at(yy));
		}
	}
	return 0;
}
