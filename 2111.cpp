#include <cstdio>
#include <cmath>

using namespace std;
class AvlTree {
    struct AvlNode
    {   int data;
        AvlNode   *left;
        AvlNode   *right;
        int       height;
		int		  size;

        AvlNode( const int &element , AvlNode *lt,
                 AvlNode *rt, int h=0, int s=1 )
            : data(element), left( lt ), right( rt ), height(h), size(s) { }
    };

    AvlNode *root;
public:
    AvlTree( AvlNode *t = NULL ) {
        root = t;
    }
    ~AvlTree( ) {
        makeEmpty( root);
    }
	int size() const
	{
		return root->size;
	}
    bool find( const int & x ) const;
    void insert( const int & x ) {
        insert(x, root);
    }
    void remove( const int & x ) {
        remove(x, root);
    }
	int nearest( int a ) const
	{
		return nearest(root,a);
	}
	AvlNode * smallest() const
	{
		return smallest(root);
	}
	AvlNode * largest() const
	{
		return largest(root);
	}
private:
    void insert( const int & x, AvlNode * & t ) ;
    bool remove( const int & x, AvlNode * & t ) ;
    void makeEmpty( AvlNode * & t );
    int height( AvlNode *t ) const
    {
        return t == NULL ? -1 : t->height;
    }
    void LL( AvlNode * & t );
    void LR( AvlNode * & t );
    void RL( AvlNode * & t );
    void RR( AvlNode * & t );
    int max(int a, int b) const {
        return (a>b)?a:b;
    }
	int min(int a, int b) const {
		return (a>b)?b:a;
	}
	AvlNode * smallest(AvlNode * t) const
	{
		if(t == NULL) return NULL;
		if(t->left) return smallest(t->left);
		return t;
	}
	AvlNode * largest(AvlNode * t) const
	{
		if(t == NULL) return NULL;
		if(t->right) return largest(t->right);
		return t;
	}
	int nearest(AvlNode * t, int a) const
	{
		if(t == NULL) return -1;
		if(t->data == a) return 0;
		if(t->data < a)
		{
			AvlNode * p = smallest(t->right);
			if(p)
			{
				if(p->data == a) return 0;
				if(p->data < a) return nearest(t->right,a);
				return min(abs(t->data-a),abs(p->data-a));
			}
			return abs(t->data-a);
		}
		else
		{
			AvlNode * p = largest(t->left);
			if(p)
			{
				if(p->data == a) return 0;
				if(p->data > a) return nearest(t->left,a);
				return min(abs(t->data-a),abs(p->data-a));
			}
			return abs(t->data-a);
		}
	}
};

void AvlTree::makeEmpty( AvlNode * & t )
{
	if( t == NULL ) return;
	makeEmpty( t->left );
	makeEmpty( t->right );
	delete t;
	t = NULL;
}

bool AvlTree::find( const int & x ) const
{   AvlNode *t = root;
    while (t!=NULL && t->data != x)
        if (t->data > x) t = t->left;
        else t = t->right;
    if (t==NULL) return false;
    else return true;
}

void AvlTree::insert( const int & x, AvlNode * & t )
{   if( t == NULL )
        t = new AvlNode( x, NULL, NULL );
    else if( x < t->data ) {
        insert( x, t->left );
        if( height( t->left ) - height( t->right ) == 2 )
            if( x < t->left->data ) LL( t );
            else LR(t);
    }
    else if( t->data < x )  {
        insert( x, t->right );
        if( height( t->right ) - height( t->left ) == 2 )
            if( t->right->data < x ) RR(t);
            else RL(t);
    }
    t->height = max( height( t->left ) , height( t->right ) ) + 1;
	t->size++;
}

void AvlTree::LL( AvlNode * & t )
{
    AvlNode *t1 = t->left;
    t->left = t1->right;
    t1->right = t;
    t->height = max( height( t->left ),  height( t->right ) ) + 1;
    t1->height = max( height( t1->left ), height(t)) + 1;
    t = t1;
}

void AvlTree::RR( AvlNode * & t )
{
    AvlNode *t1 = t->right;
    t->right = t1->left;
    t1->left = t;
    t->height = max( height( t->left ),  height( t->right ) ) + 1;
    t1->height = max( height( t1->right ), height(t)) + 1;
    t = t1;
}

void AvlTree::LR( AvlNode * & t )
{
    RR( t->left );
    LL( t );
}

void AvlTree::RL( AvlNode * & t )
{
    LL( t->right );
    RR( t );
}

bool AvlTree::remove( const int & x, AvlNode * & t )
{   bool stop =false;
    int subTree;
    if( t == NULL )     return true;
	t->size--;
    if( x < t->data )   {
        stop = remove( x, t->left );
        subTree = 1;
    }
    else if( t->data < x )
    {
        stop = remove( x, t->right );
        subTree = 2;
    }
    else if( t->left != NULL && t->right != NULL ) {
        AvlNode *tmp = t->right;
        while(tmp->left != NULL) tmp = tmp->left;
        t->data = tmp->data;
        stop = remove( t->data, t->right );
        subTree = 2;
    }
    else   {
        AvlNode *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
        return false;
    }
    if (stop) return true;
    int bf;
    switch(subTree) {
    case 1:
        bf = height(t->left) - height(t->right) + 1;
        if (bf == 0) return true;
        if (bf == 1)  return false;
        if (bf ==-1) {
            int bfr = height(t->right->left) - height(t->right->right);
            switch (bfr) {
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
        bf = height(t->left) - height(t->right) -1;
        if (bf == 0) return true;
        if (bf == -1) return false;
        if (bf == 1) {
            int bfl = height(t->left->left)
                      - height(t->left->right);
            switch (bfl) {
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

int main()
{
	AvlTree t;
	int M;
	scanf("%d",&M);
	for(int i = 0; i < M; i++)
	{
		int o,x;
		scanf("%d%d",&o,&x);
		switch(o)
		{
		case 0:
			printf("%d\n",t.nearest(x));
			break;
		case 1:
			t.insert(x);
			break;
		case 2:
			t.remove(x);
		}
	}
	return 0;
}
