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
	if(b1.size < b2.size) return true;
	if(b1.size > b2.size) return false;
	return b1.index < b2.index;
}


bool operator>(const Box &b1, const Box &b2)
{
	if(b1.size > b2.size) return true;
	if(b1.size < b2.size) return false;
	return b1.index > b2.index;
}

/**
 * TreeMap is the balanced-tree implementation of map. The iterators must
 * iterate through the map in the natural order (operator<) of the key.
 */

template<class K, class V>
class TreeMap
{
public:
    class Entry
    {
    public:
        K key;
        V value;
        Entry(K k, V v)
        {
            key = k;
            value = v;
        }

        K getKey() const
        {
            return key;
        }

        V getValue() const
        {
            return value;
        }
    };

	struct Node
	{
		Entry entry;
		Node *left;
		Node *right;
		Node *father;
		int height;
		int size;
		Node(const K& k, const V& v,
		Node *lt=NULL, Node *rt=NULL, Node *f=NULL,
		int h=0, int s=1)
		:entry(k,v),left(lt),right(rt),father(f),
		height(h),size(s) {}

		const Node * next() const
		{
			const Node *t = this;
			if(t->right)
			{
				const Node *tmp = t->right;
				while(tmp->left) tmp = tmp->left;
				return tmp;
			}
			while(true)
			{
				const Node *f = t->father;
				if(f==NULL) return NULL;
				if(f->left == t) return f;
				t = f;
				f = f->father;
			}
		}
	};

	Node *root;

    /**
     * TODO Constructs an empty tree map.
     */
    TreeMap(Node *t = NULL):root(t) { }

    /**
     * TODO Destructor
     */
    ~TreeMap() { makeEmpty(root); }

    /**
     * TODO Assignment operator
     */
    TreeMap &operator=(const TreeMap &x) 
	{
		makeEmpty(root);
		copyTree(root,x.root);
		return *this;
	}

    /**
     * TODO Copy-constructor
     */
    TreeMap(const TreeMap &x)
	{
		copyTree(root,x.root);
		if(root) root->father=NULL;
	}

    /**
     * TODO Removes all of the mappings from this map.
     */
    void clear()
	{
		makeEmpty(root);
	}

    /**
     * TODO Returns true if this map contains a mapping for the specified key.
     */
    bool containsKey(const K &key) const 
	{
		Node *t = root;
		while(t!=NULL && t->entry.key != key)
			if(t->entry.key > key) t = t->left;
			else t = t->right;
		return t!=NULL;
	}

    /**
     * TODO Returns true if this map maps one or more keys to the specified value.
     */
    bool containsValue(const V &value) const
	{
		return containsValue(root,value);
	}

    /**
     * TODO Returns true if this map contains no key-value mappings.
     */
    bool isEmpty() const {return root==NULL;}

    /**
     * TODO Associates the specified value with the specified key in this map.
     */
    Node *put(const K &key, const V &value)
	{
		return insert(key,value,root,NULL);
	}

	Node *rank(int k)
	{
		return rank(k,root);
	}

    void remove(const K &key)
	{
		remove(key,root);
	}

    /**
     * TODO Returns the number of key-value mappings in this map.
     */
    int size() const {return size(root);}

private:
	int max(int a,int b)
	{
		return a>b?a:b;
	}
	void makeEmpty( Node * & t)
	{
		if( t == NULL ) return;
		makeEmpty( t->left );
		makeEmpty( t->right );
		delete t;
		t = NULL;
	}

	void copyTree( Node * & t, const Node * s)
	{
		if( s == NULL )
		{
			t = NULL;
			return;
		}
		t = new Node(s->entry.key,s->entry.value);
		copyTree(t->left,s->left);
		copyTree(t->right,s->right);
		if(t->left) t->left->father = t;
		if(t->right) t->right->father = t;
		t->height = max(height(t->left),height(t->right))+1;
		t->size = size(t->left)+size(t->right)+1;
	}

	bool containsValue(Node *t, const V &value) const
	{
		if(t == NULL) return false;
		if(t->entry.value == value) return true;
		if(containsValue(t->left,value)) return true;
		if(containsValue(t->right,value)) return true;
		return false;
	}

	int height(const Node * t) const
	{
		if(t) return t->height;
		return -1;
	}

	int size(const Node * t) const
	{
		if(t) return t->size;
		return 0;
	}

	Node *rank(int k, Node *t)
	{
		if(k < 1) return NULL;
		if(k > size(t)) return NULL;
		if(k <= size(t->right)) return rank(k,t->right);
		if(k == size(t->right)+1) return t;
		return rank(k-size(t->right)-1,t->left);
	}

	Node *insert(const K &k, const V &v, Node * & t, Node *f)
	{
		Node *r = NULL;
		if(t == NULL)
		{
			t = new Node(k,v);
			t->father = f;
			return t;
		}
		else if( k < t->entry.key )
		{
			r = insert( k, v, t->left, t);
			if( height( t->left ) - height( t->right ) == 2 )
				if( k < t->left->entry.key ) LL(t);
				else LR(t);
		}
		else if( k > t->entry.key )
		{
			r = insert( k, v, t->right, t);
			if( height( t->right ) - height( t->left ) == 2 )
				if( t->right->entry.key < k ) RR(t);
				else RL(t);
		}
		else
		{
			t->entry.value = v;
			return t;
		}
		t->height = max( height( t->left ), height( t->right ) ) + 1;
		t->size = size( t->left ) + size( t->right ) + 1;
		return r;
	}

	bool remove(const K &k, Node * & t)
	{
		bool stop = false;
		int subTree;
		if(t == NULL) return true;
		t->size--;
		if(k < t->entry.key)
		{
			stop = remove(k,t->left);
			subTree = 1;
		}
		else if(t->entry.key < k)
		{
			stop = remove(k,t->right);
			subTree = 2;
		}
		else if(t->left != NULL && t->right !=NULL)
		{
			Node *tmp = t->right;
			while(tmp->left != NULL) tmp = tmp->left;
			t->entry = tmp->entry;
			stop = remove(t->entry.key,t->right);
			subTree = 2;
		}
		else
		{
			Node *oldNode = t;
			t = (t->left != NULL) ? t->left : t->right;
			if(t)
			{
				if(t->left) t->left->father = t;
				if(t->right) t->right->father = t;
			}
			delete oldNode;
			return false;
		}
		if(stop) return true;
		int bf;
		switch(subTree)
		{
		case 1:
			bf = height(t->left) - height(t->right) + 1;
			if(bf == 0) return true;
			if(bf == 1) return false;
			if(bf == -1)
			{
				int bfr = height(t->right->left) - height(t->right->right);
				switch(bfr)
				{
				case 0:
					RR(t);
					return true;
				case -1:
					RR(t);
					return false;
				default:
					RL(t);
					return false;
				}
			}
			break;
		case 2:
			bf = height(t->left) - height(t->right) - 1;
			if(bf == 0) return true;
			if(bf == -1) return false;
			if(bf == 1)
			{
				int bfl = height(t->left->left)-height(t->left->right);
				switch(bfl)
				{
				case 0:
					LL(t);
					return true;
				case 1:
					LL(t);
					return false;
				default:
					LR(t);
					return false;
				}
			}
		}
	}

	void LL(Node * & t)
	{
		Node *t1 = t->left;
		t->left = t1->right;
		t1->right = t;
		t1->father = t->father;
		t->father = t1;
		if(t->left) t->left->father = t;
		t->height = max( height( t->left ),  height( t->right ) ) + 1;
		t1->height = max( height( t1->left ), height(t)) + 1;
		t->size = size( t->left ) + size( t->right) + 1;
		t1->size = size( t1->left ) + size( t1->right ) + 1;
		t = t1;
	}

	void RR(Node * & t)
	{
		Node *t1 = t->right;
		t->right = t1->left;
		t1->left = t;
		t1->father = t->father;
		t->father = t1;
		if(t->left) t->left->father = t;
		t->height = max( height( t->left ),  height( t->right ) ) + 1;
		t1->height = max( height( t1->right ), height(t)) + 1;
		t->size = size( t->left ) + size( t->right) + 1;
		t1->size = size( t1->left ) + size( t1->right ) + 1;
		t = t1;
	}

	void LR(Node * & t)
	{
		RR(t->left);
		LL(t);
	}

	void RL(Node * & t)
	{
		LL(t->right);
		RR(t);
	}

	Node *father(const Node * t)  const
	{
		if(t) return t->father;
		return NULL;
	}
};

typedef struct setLink
{
	int index;
	setLink *next;
	setLink(){}
	setLink(int i):index(i),next(NULL){}
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
	TreeMap<Box,int> T;
	vector<setLink> candies(N+1);
	vector<TreeMap<Box,int>::Node*> boxNode(N+1);
	for(int i = 1; i <= N; i++)
	{
		candies[i] = setLink(i);
		boxNode[i] = T.put(Box(i),0);
	}
	for(int i = 0; i < M; i++)
	{
		char c[2];
		scanf("%s",c);
		if(c[0] == 'C')
		{
			int x,y;
			scanf("%d%d",&x,&y);
			setLink *b = getBox(candies,x);
			setLink *c = getBox(candies,y);
			if(b->index==0 || c->index==0 || b==c) continue;
			c->next = b;
			int key = b->index;
			int size = boxNode[b->index]->entry.key.size+boxNode[c->index]->entry.key.size;
			T.remove(boxNode[c->index]->entry.key);
			T.remove(boxNode[b->index]->entry.key);
			T.put(Box(key,size),0);
		}
		else if(c[0] == 'D')
		{
			int x;
			scanf("%d",&x);
			setLink *b = getBox(candies,x);
			if(b->index==0) continue;
			T.remove(boxNode[b->index]->entry.key);
			b->index = 0;
		}
		else if(c[0] == 'Q')
		{
			int p;
			scanf("%d",&p);
			TreeMap<Box,int>::Node * q = T.rank(p);
			if(q) printf("%d\n",q->entry.key.size);
			else printf("0\n");
		}
	}
	return 0;
}
