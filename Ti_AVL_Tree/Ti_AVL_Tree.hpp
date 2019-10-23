// (c) Tivole

#include <iostream>
using namespace std;

class Ti_Node {
	int value, balance;
	Ti_Node *left, *right;
	Ti_Node() {
		left = right = NULL;
		value = balance = 0;
	}
	friend class Ti_AVL_Tree;
};

class Ti_AVL_Tree {

	Ti_Node *root;

	void Ti_Show(Ti_Node *position, int level, int *x);
	int size(Ti_Node *node);
	void DeleteAll(Ti_Node*);

	Ti_Node *Rebuild_L1(Ti_Node*);
	Ti_Node *Rebuild_L2(Ti_Node*);
	Ti_Node *Rebuild_R1(Ti_Node*);
	Ti_Node *Rebuild_R2(Ti_Node*);

	void UpDown(Ti_Node*);
	void LeftRight(Ti_Node*);
	void DownUp(Ti_Node*);

	Ti_Node *AddElement(int, Ti_Node*, int*);
	Ti_Node *DeleteElement(int, Ti_Node*, int*);

public:

	Ti_AVL_Tree();
	~Ti_AVL_Tree();

	void Ti_Show();
	void UpDown();
	void LeftRight();
	void DownUp();

	void AddElement(int);
	void DeleteElement(int);
	
};

void Ti_AVL_Tree::DeleteAll(Ti_Node *position) {
	if(position == NULL) return;
	DeleteAll(position->left);
	DeleteAll(position->right);
	delete position;
}

Ti_AVL_Tree::Ti_AVL_Tree() {
	root = NULL;
}

Ti_AVL_Tree::~Ti_AVL_Tree() {
	DeleteAll(root);
}

void Ti_AVL_Tree::UpDown() {
	UpDown(root);
}

void Ti_AVL_Tree::LeftRight() {
	LeftRight(root);
}

void Ti_AVL_Tree::DownUp() {
	DownUp(root);
}

void Ti_AVL_Tree::AddElement(int element) {
	int grow;
	root = AddElement(element, root, &grow);
}

void Ti_AVL_Tree::DeleteElement(int element) {
	int grow;
	root = DeleteElement(element, root, &grow);
}

void Ti_AVL_Tree::UpDown(Ti_Node *x) {
	if(x == NULL) return;
	cout << ' ' << x->value;
	UpDown(x->left);
	UpDown(x->right);
}


void Ti_AVL_Tree::LeftRight(Ti_Node *x) {
	if(x == NULL) return;
	LeftRight(x->left);
	cout << ' ' << x->value;
	LeftRight(x->right);
}

void Ti_AVL_Tree::DownUp(Ti_Node *x) {
	if(x == NULL) return;
	DownUp(x->left);
	DownUp(x->right);
	cout << ' ' << x->value;
}


int Ti_AVL_Tree::size(Ti_Node *node) {
	if (node == NULL)  return 0;
	else return(size(node->left) + 1 + size(node->right));
}

Ti_Node* Ti_AVL_Tree::Rebuild_L1(Ti_Node *A) {
	Ti_Node *B;
	B = A->left;
	A->left = B->right;
	B->right = A;
	if(B->balance) {
		A->balance = B->balance = 0;
	}else {
		A->balance = -1;
		B->balance = -1;
	}
	return B;
}

Ti_Node* Ti_AVL_Tree::Rebuild_L2(Ti_Node *A) {
	Ti_Node *B, *C;
	B = A->left;
	C = B->right;
	A->left = C->right;
	B->right = C->left;
	C->left = B;
	C->right = A;
	switch(C->balance) {
		case 0: A->balance = 0; B->balance = 0; break;
		case -1: A->balance = 1; B->balance = 0; break;
		case 1: A->balance = 0; B->balance = -1;
	}
	C->balance = 0;
	return C;
}

Ti_Node* Ti_AVL_Tree::Rebuild_R1(Ti_Node *A) {
	Ti_Node *B;
	B = A->right;
	A->right = B->left;
	B->left = A;
	if(B->balance) {
		A->balance = 0;
		B->balance = 0;
	}else {
		A->balance = 1;
		B->balance = -1;
	}
	return B;
}

Ti_Node* Ti_AVL_Tree::Rebuild_R2(Ti_Node *A) {
	Ti_Node *B, *C;
	B = A->right;
	C = B->left;
	B->left = C->right;
	A->right = C->left;
	C->left = A;
	C->right = B;
	switch(C->balance) {
		case 0: A->balance = 0; B->balance = 0; break;
		case -1: A->balance = 0; B->balance = 1; break;
		case 1: A->balance = -1; B->balance = 0;
	}
	C->balance = 0;
	return C;
}

Ti_Node* Ti_AVL_Tree::AddElement(int x, Ti_Node *root, int *grow) {
	int incr;
	*grow = 0;
	if(!root) {
		root = new Ti_Node;
		root->value = x;
		root->left = root->right = NULL;
		root->balance = 0;
		*grow = 1;
		return root;
	}
	if(x < root->value) {
		root->left = AddElement(x, root->left, &incr);
		if(incr) {
			switch(root->balance) {
				case 0: root->balance = -1; *grow = 1; break;
				case 1: root->balance = 0; break;
				case -1:
					switch(root->left->balance) {
						case -1: root = Rebuild_L1(root); break;
						case 1: root = Rebuild_L2(root);
					}
			}
		}
		return root;
	}
	if(x > root->value) {
		root->right = AddElement(x, root->right, &incr);
		if(incr) {
			switch(root->balance) {
				case 0:  root->balance = 1; *grow = 1; break;
				case -1: root->balance = 0; break;
				case 1:
					switch(root->right->balance) {
						case 1:  root = Rebuild_R1(root); break;
						case -1: root = Rebuild_R2(root);
					}
			}
		}
	}
	return root;
}

Ti_Node* Ti_AVL_Tree::DeleteElement(int x, Ti_Node *root, int *grow) {
	int incr;
	Ti_Node *position;
	*grow = 0;
	if(!root) return 0;
	if(x == root->value) {
		if(root->left == 0) {
			*grow = -1;
			root = root->right;
			return root;
		}
		if(root->right == 0) {
			*grow = -1;
			root = root->left;
			return root;
		}
		for(position = root->left; position->right;) position = position->right;
		root->value = position->value;
		root->left = DeleteElement(position->value, root->left, &incr);
		if(incr) {
			switch(root->balance) {
				case -1: root->balance = 0; *grow = -1; break;
				case 0:  root->balance = 1; break;
				case 1:
					switch(root->right->balance) {
						case 1:  root = Rebuild_R1(root); *grow = -1; break;
						case 0:  root = Rebuild_R1(root); break;
						case -1: root = Rebuild_R2(root); *grow = -1;
					}
			}
		}
	}else {
		if(x < root->value) {
			root->left = DeleteElement(x, root->left, &incr);
			if(incr) {
				switch(root->balance) {
					case -1: root->balance = 0; *grow = -1; break;
					case 0:  root->balance = 1; break;
					case 1:
						switch(root->right->balance) {
							case 1:  root = Rebuild_R1(root); *grow = -1; break;
							case 0:  root = Rebuild_R1(root); break;
							case -1: root = Rebuild_R2(root); *grow = -1;
						}
				}
			}
		}else {
			root->right = DeleteElement(x, root->right, &incr);
			if(incr) {
				switch(root->balance) {
					case 1: root->balance = 0; *grow = -1; break;
					case 0: root->balance = -1; break;
					case -1:
						switch(root->left->balance) {
							case -1: root = Rebuild_L1(root); *grow = -1; break;
							case 0:  root = Rebuild_L1(root); break;
							case 1:  root = Rebuild_L2(root); *grow = -1;
						}
				}
			}
		}
	}
	return root;
}

void Ti_AVL_Tree::Ti_Show(Ti_Node *position, int level, int *x) {
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

void Ti_AVL_Tree::Ti_Show() {
	int N = size(root);
	cout << "\n\n";
	int *x = new int[N];
	for(int i = 0; i < N; i++) x[i] = 0;
	Ti_Show(root, 0, x);
	cout << endl;
}
