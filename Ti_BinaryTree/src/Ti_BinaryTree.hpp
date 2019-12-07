// (c) Tivole

#include <iostream>
using namespace std;

template <class Ti_Type> class Ti_Tree;

template <class Ti_Type>
class Ti_TreeNode {
	int value;
	Ti_TreeNode *previous, *left, *right;
	Ti_TreeNode (int x = 0) {
		value = x;
		previous = left = right = NULL;
	}
	friend class Ti_Tree<Ti_Type>;
};

template <class Ti_Type>
class Ti_Tree {

	Ti_TreeNode<Ti_Type> *root;
	Ti_TreeNode<Ti_Type> *DirectSearch(Ti_Type x, Ti_TreeNode<Ti_Type> *current);

	void DeleteAll(Ti_TreeNode<Ti_Type>*);
	void ShowLR(Ti_TreeNode<Ti_Type>*);
	void ShowUD(Ti_TreeNode<Ti_Type>*);
	void ShowDU(Ti_TreeNode<Ti_Type>*);
	void Ti_Show(Ti_TreeNode<Ti_Type>*, int level, Ti_Type *x);
	int size(Ti_TreeNode<Ti_Type> *);

	void probnik(Ti_TreeNode<Ti_Type>*);

public:

	Ti_Tree();
	~Ti_Tree();

	int RootValue(Ti_Type*);
	int AddElement(Ti_Type);
	int DeleteElement(Ti_Type);


	void probnik() {
		probnik(root);
	}

	void Search(Ti_Type);

	void ShowLR() { ShowLR(root); cout << endl; }
	void ShowUD() { ShowUD(root); cout << endl; }
	void ShowDU() { ShowDU(root); cout << endl; }
	void Ti_Show();
};

template <class Ti_Type>
void Ti_Tree<Ti_Type>::probnik(Ti_TreeNode<Ti_Type>*node) {
	if(node == NULL) return;
	//
	int sizel = 0;
	if(node->left != NULL) sizel = size(node->left);
	int sizer = 0;
	if(node->right != NULL) sizer = size(node->right);
	node->value = sizer - sizel;
	//
	probnik(node->left);
	probnik(node->right);
}

template <class Ti_Type>
int Ti_Tree<Ti_Type>::size(Ti_TreeNode<Ti_Type> *node) {
	if (node == NULL)  return 0;
	else return(size(node->left) + 1 + size(node->right));
}

template <class Ti_Type>
Ti_Tree<Ti_Type>::Ti_Tree() {
	root = NULL;
}

template <class Ti_Type>
Ti_Tree<Ti_Type>::~Ti_Tree() {
	DeleteAll(root);
}

template <class Ti_Type>
int Ti_Tree<Ti_Type>::RootValue(Ti_Type *x) {
	if(root) {
		*x = root->value;
		return 1;
	}else {
		cout << "Void tree" << endl;
		return 0;
	}
}

template <class Ti_Type>
void Ti_Tree<Ti_Type>::DeleteAll(Ti_TreeNode<Ti_Type> *current) {
	if(!current) return;
	DeleteAll(current->left);
	DeleteAll(current->right);
	delete(current);
}

template <class Ti_Type>
int Ti_Tree<Ti_Type>::AddElement(Ti_Type x) {
	if(!root) {
		root = new Ti_TreeNode<Ti_Type>(x);
		return 1;
	}
	Ti_TreeNode<Ti_Type> *position, *PositionBefore;
	int direction;
	position = root;
	while(position) {
		PositionBefore = position;
		if(x < position->value) {
			position = position->left;
			direction = 0;
		}else if(x > position->value) {
			position = position->right;
			direction = 1;
		}else {
			cout << x << " already is in the tree" << endl;
			return 0;
		}
	}
	position = new Ti_TreeNode<Ti_Type>(x);
	if(direction == 0) PositionBefore->left = position;
	else PositionBefore->right = position;

	position->previous = PositionBefore;

	return 1;
}


template <class Ti_Type>
int Ti_Tree<Ti_Type>::DeleteElement(Ti_Type x) {
	Ti_TreeNode<Ti_Type> *position = NULL, *PositionOf_x = NULL;
	PositionOf_x = DirectSearch(x, root);
	if(!PositionOf_x) { cout << x << " doesn't exist" << endl; return 0; }

	cout << "Deleting " << x << endl;
	position = PositionOf_x;
	if(position->previous == NULL) {
		if(position->left != NULL) {
			position = position->left;
			while(position->right) position = position->right;
			PositionOf_x->value = position->value;
		}else if(position->right != NULL) {
			position = position->right;
			while(position->left) position = position->left;
			PositionOf_x->value = position->value;
		}else {
			root = NULL;
			return 1;
		}
	}else	if((position->left != NULL) && (position->right != NULL)) {
	  position = position->left;
	  while(position->right) position = position->right;
	  PositionOf_x->value = position->value;
	}

	if(position->previous != NULL) {
		if((position->left == NULL) && (position->right == NULL)) {
			if(position->previous->left == position) position->previous->left = NULL;
			else position->previous->right = NULL;
		}else if(position->left != NULL) {
			if(position->previous->left == position) position->previous->left = position->left;
			else position->previous->right = position->left;
			position->left->previous = position->previous;
		}else if(position->right != NULL) {
			if(position->previous->right == position) position->previous->right = position->right;
			else position->previous->left = position->right;
			position->right->previous = position->previous;
		}
	}

	delete position;
	return 1;
}

template <class Ti_Type>
void Ti_Tree<Ti_Type>::ShowLR(Ti_TreeNode<Ti_Type> *position) {
	if(!position) return;

	if(position->left) cout << "L";
	ShowLR(position->left);

	cout << position->value;

	if(position->right) cout << "R";
	ShowLR(position->right);

	if(position->previous) cout << "P";
}

template <class Ti_Type>
void Ti_Tree<Ti_Type>::ShowUD(Ti_TreeNode<Ti_Type> *position) {
	if(!position) return;
	cout << position->value << " ";
	ShowUD(position->left);
	ShowUD(position->right);
}

template <class Ti_Type>
void Ti_Tree<Ti_Type>::ShowDU(Ti_TreeNode<Ti_Type> *position) {
	if(!position) return;
	ShowDU(position->left);
	ShowDU(position->right);
	cout << position->value << " ";
}

template <class Ti_Type>
Ti_TreeNode<Ti_Type> *Ti_Tree<Ti_Type>::DirectSearch(Ti_Type x, Ti_TreeNode<Ti_Type> *start) {
	while(start) {
		if(x == start->value) break;
		start = (x < start->value) ? start->left : start->right;
	}
	return start;
}

template <class Ti_Type>
void Ti_Tree<Ti_Type>::Search(Ti_Type x) {
	Ti_TreeNode<Ti_Type> *Searched = DirectSearch(x, root);
	if(Searched != NULL) cout << "Searched = " << Searched->value << endl;
	else cout << "Searched = NULL";
}

template <class Ti_Type>
void Ti_Tree<Ti_Type>::Ti_Show(Ti_TreeNode<Ti_Type> *position, int level, Ti_Type *x) {
	if(!position) return;
	x[level] = 0;
	Ti_Show(position->right, level + 1, x);
	x[level] = 1;
	int invertor = 0;
	if (level != 0) cout << "      ";
	for(int i = 1; i < level; i++) {
		invertor = (x[i] != x[i-1]) ? 1 : 0;

		if (invertor) cout<<"|     ";
		else cout<<"      ";
	}
	cout << "|--";
	cout.width(2);
	cout << position->value << " |" << endl;
	x[level] = 1;
	Ti_Show(position->left, level + 1, x);
	x[level] = 0;
}

template <class Ti_Type>
void Ti_Tree<Ti_Type>::Ti_Show() {
	int N = size(root);
	if(N == 0) { cout << "Tree is empty"; return; }
	Ti_Type *x = new Ti_Type[N];
	for(int i = 0; i < N; i++) x[i] = 0;
	Ti_Show(root, 0, x);
	cout << endl;
}
