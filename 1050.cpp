#include <cstdio>
#include <cstdlib>
#include <functional>
#include <cassert>
using namespace std;

class ElementNotExist{};

template<class Type>
struct Node
{
    Type data;
    int dist;
    Node<Type> *left;
    Node<Type> *right;

    Node(Type val)
    {
        data = val;
        dist = 0;
        left = right = NULL;
    }

    ~Node()
    {
    }
};


template <class Type,class Compare = less<Type> >
class LeftistTree
{
private:
    Node<Type> *root;

    
    void Delete(Node<Type> *node)
    {
        if(NULL != node)
        {
            Delete(node->left);
            Delete(node->right);
            delete node;
            //node = NULL;
        }
    }

    
    //static bool HasLeft(Node<Type>* node)
    //{
    //  if(!node) return false;
    //  return node->left;
    //}

    
    static Node<Type>*& Left(Node<Type>*& node)
    {
        assert(NULL != node);
        return node->left;
    }

   
    //static bool HasRight(Node<Type>* node)
    //{
    //  if(!node) return false;
    //  return node->right;
    //}

    
    static Node<Type>*& Right(Node<Type>*& node)
    {
        assert(NULL != node);
        return node->right;
    }

    static int Dist(Node<Type>* node)
    {
        if(NULL == node) return -1;
        return node->dist;
    }

    
    static void Swap(Node<Type>*& left,Node<Type>*& right)
    {
        Node<Type> *temp = left;
        left = right;
        right = temp;
    }

    static Node<Type>*& Merge(Node<Type>*& t1, Node<Type>*& t2)
    {

        if(NULL == t1)
            return t2;
        else if(NULL == t2)
            return t1;

        if( Compare()(t2->data, t1->data) ) 
            Swap(t1,t2);
        Right(t1) = Merge(Right(t1), t2);

        if( Dist(Right(t1)) > Dist(Left(t1)) )
            Swap( Left(t1),Right(t1) );
        if( NULL == Right(t1) )
            t1->dist = 0;
        else t1->dist = Dist(Right(t1)) + 1;


        return t1;
    }

public:

    LeftistTree(): root(NULL)
    {
    }

    ~LeftistTree()
    {
        Delete(root);
    }

    void Insert(Type val)
    {
        Node<Type> *newNode;
        newNode = new Node<Type>(val); root = Merge(root, newNode); }

    void DeleteRoot()
    {
        if(NULL == root)
        {
			return;
        }
        Node<Type> *p = root;
        root = Merge(p->left, p->right);
        delete p;
    }

    void Merge(LeftistTree<Type,Compare>& t2)
    {
        root = Merge(root, t2.root);
        t2.root = NULL;
    }

    Type Root()
    {
        if(NULL == root)
        {
            return -1;
        }
        return root->data;
    }

};

int main()
{
	int N,M;
	LeftistTree<int> gs[300000];
	scanf("%d%d",&N,&M);
	for(int i = 0; i < N; i++)
	{
		int a;
		scanf("%d",&a);
		gs[i].Insert(a);
	}
	for(int i = 0; i < M; i++)
	{
		int o,a,b;
		scanf("%d",&o);
		switch(o)
		{
		case 0:
			scanf("%d%d",&a,&b);
			gs[a].Merge(gs[b]);
			break;
		case 1:
			scanf("%d",&a);
			printf("%d\n",gs[a].Root());
			gs[a].DeleteRoot();
			break;
		case 2:
			scanf("%d%d",&a,&b);
			gs[a].Insert(b);
		}
	}
	return 0;
}
