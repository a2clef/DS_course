#include <iostream>
#include <time.h>
#include <stdlib.h>


#define MAX_COUNT_1	30
//#define MAX_COUNT_2	20000
#define RAND_MAX_1	100
//#define RAND_MAX_2	1000000
#define random(x) (rand()%x)
#define WRITE_WALK_RES_TO_ARR 1
#define DELETE_COUNT 5

int arr1[MAX_COUNT_1], walkres[MAX_COUNT_1], resc;

using namespace std;


template <class T>
class BSTNode
{
public:
	T			key;
	BSTNode*	left;
	BSTNode*	right;
	BSTNode(const T& key_in, BSTNode *pl, BSTNode *pr)		//a constructor
	{
		key = key_in;
		left = pl;
		right = pr;
	};
};


template <class T>
class BSTree
{
public:
	BSTree();					//default constructor
	~BSTree();					//default destructor

	BSTNode<T>* search(const T& x);		//search
	void insert(const T& x);	//insert
	void remove(const T& x);	//delete
	void clean();				//free all space, init the tree
	void Walk_Tree_Mid();		//walk the tree in mid order

	const T& find_Max();		//may be useless,bur their reloaded function is useful
	const T& find_Min();

private:
	BSTNode<T>*	root;
	//function reloaded for recursive usage
	BSTNode<T>* search(const T& x, const BSTNode<T>* ptrn);
	void insert(const T& x, BSTNode<T>* &ptrn);			//may change the pointer,shouldnt be const pointer
	void remove(const T& x, BSTNode<T>* &ptrn);			//NOTICE the reference is necessary for deletion
	void clean(BSTNode<T>* &ptrn);
	void Walk_Tree_Mid(const BSTNode<T>* ptrn);

	BSTNode<T>* find_Max(BSTNode<T>* nptr);
	BSTNode<T>* find_Min(BSTNode<T>* nptr);
};

template <class T>
BSTree<T>::BSTree()				//default constructor, make a empty tree
{
	root = NULL;
};
template <class T>
BSTree<T>::~BSTree()			//default destructir, clean the memory
{
	clean();
};

template <class T>
void BSTree<T>::clean()			//recursively delete the tree
{
	clean(root);
};
template <class T>
void BSTree<T>::clean(BSTNode<T>* &nptr)
{
	if (nptr)
	{
		clean((*nptr).left);
		clean((*nptr).right);
		delete nptr;
	};
	nptr = NULL;
};

template <class T>
const T& BSTree<T>::find_Max()
{
	return find_Max(root)->key;
}
template <class T>
BSTNode<T>* BSTree<T>::find_Max(BSTNode<T>* ptrn)
{
	if (ptrn)
		while (ptrn->right)
			ptrn = ptrn->right;
	return ptrn;
};

template <class T>
const T& BSTree<T>::find_Min()
{
	return find_Min(root)->key;
}
template <class T>
BSTNode<T>* BSTree<T>::find_Min(BSTNode<T>* ptrn)
{
	if (ptrn)
		while (ptrn->left)
			ptrn = ptrn->left;
	return ptrn;
};


template <class T>
BSTNode<T>* BSTree<T>::search(const T& x)
/*
	search the BST for a T object
	call a reloaded recursive function
	*/
{
	return search(const T& x, root);
};
template <class T>
/*
	recursive function to search the tree
	return address if found, return NULL otherwise
	*/
BSTNode<T>* BSTree<T>::search(const T& x, const BSTNode<T>* nptr)
{
	if (nptr == NULL)
		return NULL;

	if (x < (*nptr).key)
		return search(x, (*nptr).left);

	if (x >(*nptr).key)
		return search(x, (*nptr).right);

	return nptr;
};

template <class T>
void BSTree<T>::insert(const T& x)
{
	insert(x, root);
};
template <class T>
void BSTree<T>::insert(const T& x, BSTNode<T>* &nptr)
/*
	insert a element into the tree
	*/
{
	if (!nptr)
	{
		nptr = new BSTNode<T>(x, NULL, NULL);		//using a constructor of a class object
		return;
	};
	if (x < nptr->key)
		insert(x, nptr->left);
	if (x>nptr->key)
		insert(x, nptr->right);
	/*
	if running reachs here, means the element already
	exists. in this case, do nothing
	*/
};

template <class T>
void BSTree<T>::remove(const T& x)
{
	remove(x, root);
};
template <class T>
void BSTree<T>::remove(const T& x, BSTNode<T>* &ptrn)		//EDITION2 learned form sld
{
	if (!ptrn)			//if the element is not found
		return;
	if (x > ptrn->key)
	{
		remove(x, ptrn->right);
		return;
	};
	if (x < ptrn->key)
	{
		remove(x, ptrn->left);
		return;
	};
	if (ptrn->left && ptrn->right)
	{
		ptrn->key = find_Min(ptrn->right)->key;
		remove(ptrn->key, ptrn->right);
	}
	else
	{
		BSTNode<T> *oldNode = ptrn;
		ptrn = (ptrn->left) ? ptrn->left : ptrn->right;
		delete oldNode;
	}
};

template <class T>
void BSTree<T>::Walk_Tree_Mid()
{
	resc = 0;
	Walk_Tree_Mid(root);
	cout << endl;
};
template <class T>
void BSTree<T>::Walk_Tree_Mid(const BSTNode<T>* ptrn)
{
	if (ptrn)
	{
		Walk_Tree_Mid(ptrn->left);
		cout << ptrn->key << ' ';
		if (WRITE_WALK_RES_TO_ARR)
		{
			walkres[resc] = ptrn->key;
			resc++;
		};
		Walk_Tree_Mid(ptrn->right);
	}
	return;
};

int fold_Find(int num)
{
	int a = 0, b = resc - 1,mid;
	while (a <= b)
	{
		mid = (a + b) / 2;
		if (walkres[mid] == num)
			return mid;
		else if (walkres[mid] > num)
			b = mid - 1;
		else
			a = mid + 1;
	};
	/*
	 code shouldnt reach this place,
	 means the element is not found.
	*/
	return -998;
};

int main()
{
	cout << "Generating random array of " << MAX_COUNT_1 << " elements." << endl;
	srand((unsigned)time(0));
	for (int i = 0; i < MAX_COUNT_1; i++)
	{
		arr1[i] = rand() % MAX_COUNT_1;
	};
	cout << "The array is:" << endl;
	for (int i = 0; i < MAX_COUNT_1; i++)
		cout << arr1[i] << ' ';

	cout << endl << "initializing BST" << endl;
	BSTree<int> BST_int1;

	cout << "inserting elements" << endl;
	for (int i = 0; i < MAX_COUNT_1; i++)
		BST_int1.insert(arr1[i]);

	cout << "Walk the tree:" << endl;
	BST_int1.Walk_Tree_Mid();
	cout << resc << " elements remaining." << endl;
	cout << "--------------------------------------------------------" << endl;
	for (int i = 0; i < DELETE_COUNT; i++)
	{
		int pos = rand() % resc;
		cout << "delete element:" << walkres[pos] << endl;
		BST_int1.remove(walkres[pos]);
		cout << "Walk the tree again:" << endl;
		BST_int1.Walk_Tree_Mid();
		cout << resc << " elements remaining." << endl;
	};
	cout << "--------------------------------------------------------" << endl;
	for (int i = 0; i < DELETE_COUNT; i++)
	{
		int pos = rand() % resc;
		cout << "find element:" << walkres[pos] << " in position:" << pos << endl;
		cout << "Located position is:" << fold_Find(walkres[pos]) << endl;
	};



	return 0;
};