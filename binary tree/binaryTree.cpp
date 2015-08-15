#include <iostream>

using namespace std;

template <class T>
class binaryTreeNode
{
public:
	binaryTreeNode() :key(T()), parent(NULL), left(NULL), right(NULL) {}
	T key;
	binaryTreeNode<T>* parent;
	binaryTreeNode<T>* left;
	binaryTreeNode<T>* right;
};

template <class T>
class binaryTree
{
public:
	binaryTree();
	int search_key(const T& k) const;
	int get_minmum(T& bitmin) const;
	int get_maxmum(T& bitmax) const;
	int get_successor(const T& k, T& bit) const;
	int get_predecessor(const T& k, T& bit) const;
	int insert_key(const T& k);
	int delete_key(const T& k);
	void inorder_tree_walk() const;
	binaryTreeNode<T>* get_root() const;

	~binaryTree();
private:
	binaryTreeNode<T>* root;
	static  binaryTreeNode<T>* NIL;
	binaryTreeNode<T>* get_parent(binaryTreeNode<T>* pnode) const;
	binaryTreeNode<T>* get_left(binaryTreeNode<T>* pnode) const;
	binaryTreeNode<T>* get_right(binaryTreeNode<T>* pnode) const;
	T get_key(binaryTreeNode<T>* pnode) const;
	void transplant(binaryTreeNode<T> *pnode, binaryTreeNode<T> *qnode);
	binaryTreeNode<T>* get_maxmum(binaryTreeNode<T> *subtree) const;
	binaryTreeNode<T>* get_minmum(binaryTreeNode<T> *subtree) const;
	binaryTreeNode<T>* get_successor(binaryTreeNode<T> *pnode) const;
	binaryTreeNode<T>* get_predecessor(binaryTreeNode<T> *pnode) const;
	binaryTreeNode<T>* search_tree_node(const T& k)const;
	void inorder_tree_walk(binaryTreeNode<T> * tree)const;
	void make_empty(binaryTreeNode<T>* root);
};

template <class T>
binaryTreeNode<T>* binaryTree<T>::NIL = new binaryTreeNode<T>;

template <class T>
binaryTree<T>::binaryTree()
{
	root = NULL;
}

template <class T>
int binaryTree<T>::search_key(const T& k) const
{
	return (NIL != search_tree_node(k));
}

template <class T>
binaryTreeNode<T>* binaryTree<T>::get_root() const
{
	return root;
}

template <class T>
binaryTreeNode<T>* binaryTree<T>::get_parent(binaryTreeNode<T>* pnode) const
{
	return pnode->parent;
}

template < class T>
binaryTreeNode<T>* binaryTree<T>::get_left(binaryTreeNode<T>* pnode) const
{
	return pnode->left;
}

template < class T>
binaryTreeNode<T>* binaryTree<T>::get_right(binaryTreeNode<T>* pnode) const
{
	return pnode->right;
}

template <class T>
T binaryTree<T>::get_key(binaryTreeNode<T>* pnode) const
{
	return pnode->key;
}

template <class T>
void binaryTree<T>::make_empty(binaryTreeNode<T>* bitree)
{
	if (bitree)
	{
		binaryTreeNode<T> *pleft  = bitree->left;
		binaryTreeNode<T>* pright = bitree->right;
		delete bitree;
		if (pleft != NIL)
			make_empty(pleft);
		if (pright != NIL)
			make_empty(pright);
	}
}


template <class T>
binaryTreeNode<T>* binaryTree<T>::search_tree_node(const T & k) const
{
	binaryTreeNode<T>* pnode = root;
	while (pnode != NULL)
	{
		if (pnode->key < k)
			pnode = pnode->right;
		else if (pnode->key > k)
			pnode = pnode->left;
		else
			break;
	}
	return pnode;
}

template <class T>
binaryTree<T>::~binaryTree()
{
	make_empty(root);
}

template<class T>
void binaryTree<T>::inorder_tree_walk() const
{
	if (root != NULL)
		inorder_tree_walk(root);
	else
		cout << "The binary is empty." << endl;
}

template <class T>
void binaryTree<T>::inorder_tree_walk(binaryTreeNode<T>* tree) const
{
	if (tree != NIL)
	{
		inorder_tree_walk(tree->left);
		cout << tree->key<<endl;
		inorder_tree_walk(tree->right);
	}
}

template <class T>
int binaryTree<T>::get_minmum(T& bitmin) const
{
	if (root)
	{
		bitmin = get_minmum(root)->key;
		return 0;
	}
	return -1;
}

template <class T>
binaryTreeNode<T>* binaryTree<T>::get_minmum(binaryTreeNode<T>* tree) const
{
	binaryTreeNode<T>* pnode = tree;
	while (pnode->left != NIL)
	{
		pnode = pnode->left;
	}
	return pnode;
}

template <class T>
int binaryTree<T>::get_maxmum(T& bitmax) const
{
	if (root)
	{
		bitmax = get_maxmum(root)->key;
		return 0;
	}
	return -1;
}

template <class T>
binaryTreeNode<T>* binaryTree<T>::get_maxmum(binaryTreeNode<T>* tree) const
{
	binaryTreeNode<T>* pnode = tree;
	while (pnode->right != NIL)
	{
		pnode = pnode->right;
	}
	return pnode;
}

template < class T>
int binaryTree<T>::get_successor(const T& k, T& bit) const
{
	if (root)
	{
		binaryTreeNode<T>* pnode = search_tree_node(k);
		if (pnode != NIL)
		{
			pnode = get_successor(pnode);
			if (pnode != NIL)
			{
				bit = pnode->key;
				return 0;
			}
			return -1;
		}
		return -1;
	}
	return -1;
}

template <class T>
binaryTreeNode<T>*  binaryTree<T>::get_successor(binaryTreeNode<T>* subtree) const
{
	//cout << get_key(subtree) << endl;
	if (subtree->right != NIL)
	{
		return get_minmum(subtree->right);
	}
	binaryTreeNode<T>* parentnode = get_parent(subtree);
	while (parentnode != NIL && subtree == parentnode->right)
	{
		subtree = parentnode;
		parentnode = get_parent(parentnode);
	}
	return parentnode;
}

template < class T>
int binaryTree<T>::get_predecessor(const T& k, T& bit) const
{
	if (root)
	{
		binaryTreeNode<T>* pnode = search_tree_node(k);
		if (pnode != NIL)
		{
			pnode = get_predecessor(pnode);
			if (pnode != NIL)
			{
				bit = pnode->key;
				return 0;
			}
			return -1;
		}
		return -1;
	}
	return -1;
}

template <class T>
binaryTreeNode<T>*  binaryTree<T>::get_predecessor(binaryTreeNode<T>* subtree) const
{
	if (subtree->left != NIL)
		return get_minmum(subtree->left);
	binaryTreeNode<T>* parentnode = get_parent(subtree);
	while (parentnode != NIL && subtree == parentnode->left)
	{
		subtree = parentnode;
		parentnode = get_parent(parentnode);
	}
	return parentnode;
}

template <class T>
void binaryTree<T>::transplant(binaryTreeNode<T> *pnode, binaryTreeNode<T> *successor)
{
	if (pnode->parent == NIL)
		root = successor;
	else if (pnode == get_left(get_parent(pnode)))
		(pnode->parent)->left = successor;
	else
		(pnode->parent)->right = successor;
	if (successor != NIL)
		successor->parent = get_parent(pnode);
}

template <class T>
int binaryTree<T>::delete_key(const T& k)
{
	binaryTreeNode<T>* pnode = search_tree_node(k); //z

	if (NIL != pnode)
	{
		if (pnode->left == NIL)
			transplant(pnode, get_right(pnode));
		else if (pnode->right == NIL)
			transplant(pnode, get_left(pnode));
		else
		{
			binaryTreeNode<T>* qnode = get_minmum(pnode->right);//y
			cout << qnode->key << endl;
			if (qnode->parent != pnode)
			{
				transplant(qnode, qnode->right);
				qnode->right = pnode->right;
				pnode->right->parent = qnode;
			}
			transplant(pnode, qnode);
			qnode->left = pnode->left;
			qnode->left->parent = qnode;
		}
		delete pnode;
		return 0;
	}
	return -1;
}

template < class T>
int binaryTree<T>::insert_key(const T& k)
{	
	binaryTreeNode<T>* newnode = new binaryTreeNode<T>;
	newnode->key = k;
	newnode->left = NIL;
	newnode->right = NIL;
	newnode->parent = NIL;

	if (NULL == root)
		root = newnode;

	else
	{
		binaryTreeNode<T>* pnode = NIL;//y
		binaryTreeNode<T>* qnode = root;//x

		while (qnode != NIL)
		{
			pnode = qnode;
			if (k < qnode->key)
				qnode = qnode->left;
			else
				qnode = qnode->right;
		}
		newnode->parent = pnode;
		if (pnode == NIL)
			root = newnode;
		else if (newnode->key < pnode->key)
			pnode->left = newnode;
		else
			pnode->right = newnode;
	}
	return 0;
}


int main()
{
	binaryTree<int> bitree;
	int value;
	bitree.insert_key(66);
	bitree.insert_key(15);
	bitree.insert_key(5);
	bitree.insert_key(70);
	bitree.insert_key(20);
	bitree.insert_key(7);
	bitree.insert_key(75);
	bitree.insert_key(78);
	bitree.insert_key(60);
	bitree.insert_key(30);
	bitree.insert_key(50);
	bitree.insert_key(65);
	bitree.insert_key(25);
	bitree.insert_key(90);
	bitree.insert_key(40);
	bitree.insert_key(55);

	cout << "root is: " << bitree.get_root()->key << endl;
	
	cout << "Inorder walk binary black tree:" << endl;
	bitree.inorder_tree_walk();
	
	if (bitree.get_minmum(value) == 0)
		cout << "minmum is: " << value << endl;
	
	if (bitree.get_maxmum(value) == 0)
		cout << "maxmum is: " << value << endl;

	int val(66);

	if (bitree.search_key(val) != 0)
		cout << val << "is found." << endl;

	if (bitree.get_successor(val, value) == 0)
		cout <<val<< "'s successor is: " << value << endl;
	
	if (bitree.get_predecessor(val, value) == 0)
		cout << val<<"'s predecessor is: " << value << endl;
	
	if (bitree.delete_key(val) == 0)
		cout << "delete "<<val<<" successfully" << endl;

	if (bitree.delete_key(65) == 0)
		cout << "delete 65 successfully" << endl;

	cout << "root is: " << bitree.get_root()->key << endl;
	cout << "Inorder walk red black tree:" << endl;
	bitree.inorder_tree_walk();

	if (bitree.delete_key(60) == 0)
		cout << "delete 60 successfully" << endl;
	bitree.search_key(20);

	cout << "root is: " << bitree.get_root()->key << endl;
	cout << "Inorder walk red black tree:" << endl;
	bitree.inorder_tree_walk();
	return 0;
}
