// (c) Tivole

#include <iostream>

using namespace std;

#define BLACK 0
#define RED 1

template <class Ti_Type> class Ti_RBTree;

template <class Ti_Type>
class Ti_TreeNode {
	Ti_Type value;
	bool color;
	Ti_TreeNode *left, *right;

	Ti_TreeNode() {
		left = right = NULL;
		value = 0;
		color = 0;
	}
	friend class Ti_RBTree<Ti_Type>;
};

template <class Ti_Type>
class Ti_RBTree {

	Ti_TreeNode<Ti_Type> *root;

	Ti_TreeNode<Ti_Type>* Rebuild_LL(Ti_TreeNode<Ti_Type>*);
	Ti_TreeNode<Ti_Type>* Rebuild_LR(Ti_TreeNode<Ti_Type>*);
	Ti_TreeNode<Ti_Type>* Rebuild_RR(Ti_TreeNode<Ti_Type>*);
	Ti_TreeNode<Ti_Type>* Rebuild_RL(Ti_TreeNode<Ti_Type>*);

	Ti_TreeNode<Ti_Type> *DirectSearch(Ti_Type x, Ti_TreeNode<Ti_Type> *current);
	Ti_TreeNode<Ti_Type>* AddElement(Ti_Type, Ti_TreeNode<Ti_Type>*, int*);
	Ti_TreeNode<Ti_Type>* DeleteElement(Ti_Type, Ti_TreeNode<Ti_Type>*, int*);

	void ShowUD(Ti_TreeNode<Ti_Type>*);
	void ShowLR(Ti_TreeNode<Ti_Type>*);
	void ShowDU(Ti_TreeNode<Ti_Type>*);
	void Ti_Show(Ti_TreeNode<Ti_Type>*, int, Ti_Type*);

	int size(Ti_TreeNode<Ti_Type>*);
	int Search(Ti_Type);
	void DeleteAll(Ti_TreeNode<Ti_Type>*);

public:

	Ti_RBTree() { root = NULL; }
	~Ti_RBTree();

	void ShowUD() { ShowUD(root); cout << endl; }
	void ShowDU() { ShowDU(root); cout << endl; }
	void ShowLR() { ShowLR(root); cout << endl; }
	void Ti_Show();
	int RootValue(Ti_Type*);

	void AddElement(Ti_Type x) {
		if(Search(x)) cout << x << " already is in the tree!" << endl;
		else { int grow; root = AddElement(x, root, &grow); }
	}

	void DeleteElement(Ti_Type x) {
		if(Search(x)) { int grow; root = DeleteElement(x, root, &grow); }
		else cout << x << " doesn't exist!" << endl;
	}

};

template <class Ti_Type>
Ti_RBTree<Ti_Type>::~Ti_RBTree() {
	DeleteAll(root);
}

template <class Ti_Type>
void Ti_RBTree<Ti_Type>::DeleteAll(Ti_TreeNode<Ti_Type> *position) {
	if(position == NULL) return;
	DeleteAll(position->left);
	DeleteAll(position->right);
	delete position;
}

template <class Ti_Type>
void Ti_RBTree<Ti_Type>::ShowUD(Ti_TreeNode<Ti_Type> *position) {
	if(!position) return;
	cout << position->value << ' ';
	ShowUD(position->left);
	ShowUD(position->right);
}

template <class Ti_Type>
void Ti_RBTree<Ti_Type>::ShowLR(Ti_TreeNode<Ti_Type> *position) {
	if(!position) return;
	ShowLR(position->left);
	cout << position->value << ' ';
	ShowLR(position->right);
}

template <class Ti_Type>
void Ti_RBTree<Ti_Type>::ShowDU(Ti_TreeNode<Ti_Type> *position) {
	if(!position) return;
	ShowDU(position->left);
	ShowDU(position->right);
	cout << position->value << ' ';
}

template <class Ti_Type>
int Ti_RBTree<Ti_Type>::RootValue(Ti_Type *x) {
	if(root) {
		*x = root->value;
		return 1;
	}else {
		cout << "Void tree!" << endl;
		return 0;
	}
}

template <class Ti_Type>
Ti_TreeNode<Ti_Type> *Ti_RBTree<Ti_Type>::DirectSearch(Ti_Type x, Ti_TreeNode<Ti_Type> *start) {
	while(start) {
		if(x == start->value) break;
		start = (x < start->value) ? start->left : start->right;
	}
	return start;
}

template <class Ti_Type>
int Ti_RBTree<Ti_Type>::Search(Ti_Type x) {
	Ti_TreeNode<Ti_Type> *Searched = DirectSearch(x, root);
	return (Searched != NULL) ? 1 : 0;
}

template <class Ti_Type>
int Ti_RBTree<Ti_Type>::size(Ti_TreeNode<Ti_Type> *node) {
	if (node == NULL)  return 0;
	else return(size(node->left) + 1 + size(node->right));
}

template <class Ti_Type>
Ti_TreeNode<Ti_Type>* Ti_RBTree<Ti_Type>::Rebuild_LL(Ti_TreeNode<Ti_Type> *A) {
	Ti_TreeNode<Ti_Type> *B;
	B = A->left;
	A->left = B->right;
	B->right = A;
	return B;
}

template <class Ti_Type>
Ti_TreeNode<Ti_Type>* Ti_RBTree<Ti_Type>::Rebuild_LR(Ti_TreeNode<Ti_Type> *A) {
	Ti_TreeNode<Ti_Type> *B, *C;
	B = A->left;
	C = B->right;
	A->left = C->right;
	B->right = C->left;
	C->left = B;
	C->right = A;
	return C;
}

template <class Ti_Type>
Ti_TreeNode<Ti_Type>* Ti_RBTree<Ti_Type>::Rebuild_RR(Ti_TreeNode<Ti_Type> *A) {
	Ti_TreeNode<Ti_Type> *B;
	B = A->right;
	A->right = B->left;
	B->left = A;
	return B;
}

template <class Ti_Type>
Ti_TreeNode<Ti_Type>* Ti_RBTree<Ti_Type>::Rebuild_RL(Ti_TreeNode<Ti_Type> *A) {
	Ti_TreeNode<Ti_Type> *B, *C;
	B = A->right;
	C = B->left;
	B->left = C->right;
	A->right = C->left;
	C->left = A;
	C->right = B;
	return C;
}

template <class Ti_Type>
Ti_TreeNode<Ti_Type>* Ti_RBTree<Ti_Type>::AddElement(Ti_Type value, Ti_TreeNode<Ti_Type> *root, int *grow) {
	int incr;
	*grow = 0;

	if(root == NULL) {
		root = new Ti_TreeNode<Ti_Type>;
		root->value = value;
		root->left = root->right = NULL;
		root->color = BLACK;
		*grow = -1;
		return root;
	}

	if(value <= root->value) {
		root->left = AddElement(value, root->left, &incr);
		if(incr == -1) root->left->color = BLACK;
		if(incr == 1) {
			if(root->right) {
				switch(root->right->color) {
					case BLACK: root->right->color = root->left->color = RED; *grow = -1; break;
					case RED: root = Rebuild_LL(root); root->color = RED; root->left->color = root->right->color = BLACK; *grow = 0;
				}
			} else { root = Rebuild_LL(root); root->color = RED; root->left->color = root->right->color = BLACK; *grow = 0; }
		}
		if(incr == 2) {
			if(root->right) {
				switch(root->right->color) {
					case BLACK: root->right->color = root->left->color = RED; *grow = -1; break;
					case RED: root = Rebuild_LR(root); root->color = RED; root->left->color = root->right->color = BLACK; *grow = 0;
				}
			} else { root = Rebuild_LR(root); root->color = RED; root->left->color = root->right->color = BLACK; *grow = 0; }
		}
		if(root->color == BLACK && root->left->color == BLACK){ *grow = 1; }
	}
	if(value>root->value) {
		root->right = AddElement(value, root->right, &incr);
		if(incr == -1) root->right->color = BLACK;
		if(incr == 2) {
			if(root->left) {
				switch(root->left->color) {
					case BLACK: root->right->color = root->left->color = RED; *grow = -1; break;
					case RED: root = Rebuild_RR(root); root->color = RED; root->left->color = root->right->color = BLACK; *grow = 0;
				}
			} else { root = Rebuild_RR(root); root->color = RED; root->left->color = root->right->color = BLACK; *grow = 0; }
		}
		if(incr == 1) {
			if(root -> left) {
				switch(root->left->color) {
					case BLACK: root->right->color = root->left->color = RED; *grow = -1; break;
					case RED: root = Rebuild_RL(root); root->color = RED; root->left->color = root->right->color = BLACK; *grow = 0;
				}
			} else { root = Rebuild_RL(root); root->color = RED; root->left->color = root->right->color = BLACK; *grow = 0; }
		}
		if(root->color == BLACK && root->right->color == BLACK) { *grow = 2; }
	}
	return root;
}

template <class Ti_Type>
Ti_TreeNode<Ti_Type>* Ti_RBTree<Ti_Type>::DeleteElement(Ti_Type value, Ti_TreeNode<Ti_Type> *root, int *grow) {
	int incr;
	Ti_TreeNode<Ti_Type> *pos;
	*grow = 0;
	if(root == NULL) return NULL;
	if(value == root->value) {
		if(!(root->left)) {
			if(root->color == RED) {
				if(!(root->right)) *grow = -1;
				else root->right->color = RED;
			}
			root = root->right;
			return root;
		}
		if(!(root->right)){
			root = root->left;
			root->color = RED;
			return root;
		}
		for(pos = root->left; pos->right;) pos = pos->right;
		root->value = pos->value;
		root->left = DeleteElement(pos->value, root->left, &incr);
		if(incr == -1) {
			if(root->right) {
				switch(root->right->color) {
					case BLACK: root = Rebuild_RR(root); root->color = RED; root->left->color = RED; root->left->right->color = BLACK; break;
					case RED:
						if(root->right->right && root->right->left) {
							if(root->right->right->color == RED && root->right->left->color == RED) {
								root->right->color = BLACK;
								if(root->color == RED) *grow = -1;
								else { root->color = RED; *grow = 0; }
							} else if(root->right->right->color == BLACK) {
								*grow = root->color == RED ? -1 : 0;
								root = Rebuild_RR(root);
								root->color = root->left->color;
								root->right->color = root->left->color = RED;
							} else {
								*grow = root->color == RED ? -1 : 0;
								root = Rebuild_RL(root);
								root->color = root->left->color;
								root->right->color = root->left->color = RED;
							}
						} else if(!(root->right->left) && !(root->right->right)) {
							root->right->color = BLACK;
							if(root->color == RED) *grow = -1;
							else { root->color = RED; *grow = 0; }
						} else if(!root->right->left) {
							*grow = root->color == RED ? -1 : 0;
							root = Rebuild_RR(root);
							root->color = root->left->color;
							root->right->color = root->left->color = RED;
						} else if(!root->right->right) {
							*grow = root->color == RED ? -1 : 0;
							root = Rebuild_RL(root);
							root->color = root->left->color;
							root->right->color = root->left->color = RED;
						}
				}
			}
		}
		return root;
	} else {
		if(value < root->value) {
			root->left = DeleteElement(value, root->left, &incr);
			if(incr == -1) {
				if(root->right) {
					switch(root->right->color) {
						case BLACK: root = Rebuild_RR(root); root->color = RED; root->left->color = RED; root->left->right->color = BLACK; break;
						case RED:
							if(root->right->right && root->right->left) {
								if(root->right->right->color == RED && root->right->left->color == RED) {
									root->right->color = BLACK;
									if(root->color == RED) *grow = -1;
									else { root->color = RED; *grow = 0; }
								} else if(root->right->right->color == BLACK) {
									*grow = root->color == BLACK ? -1 : 0;
									root = Rebuild_RR(root);
									root->color = root->left->color;
									root->right->color = root->left->color = RED;
								} else {
									*grow = root->color == RED ? -1 : 0;
									root = Rebuild_RL(root);
									root->color = root->left->color;
									root->right->color = root->left->color = RED;
								}
							} else if(!(root->right->left) && !(root->right->right)) {
								root->right->color = BLACK;
								if(root->color == RED) *grow = -1;
								else { root->color = RED; *grow = 0; }
							} else if(!root->right->left) {
								*grow = root->color == RED ? -1 : 0;
								root = Rebuild_RR(root);
								root->color = root->left->color;
								root->right->color = root->left->color = RED;
							} else if(!root->right->right) {
								*grow = root->color == RED ? -1 : 0;
								root = Rebuild_RL(root);
								root->color = root->left->color;
								root->right->color = root->left->color = RED;
							}
					}
				}
			}
		} else {
			root->right = DeleteElement(value, root->right, &incr);
			if(incr == -1) {
				if(root->left) {
					switch(root->left->color) {
						case BLACK: root = Rebuild_LL(root); root->color = RED; root->right->color = RED; root->right->left->color = BLACK; break;
						case RED:
							if(root->left->left && root->left->right) {
								if(root->left->left->color == RED && root->left->right->color == RED) {
									root->left->color = BLACK;
									if(root->color == RED) *grow = -1;
									else { root->color = RED; *grow = 0; }
								}
								if(root->left->left->color == BLACK) {
									*grow = root->color == RED ? -1 : 0;
									root = Rebuild_LL(root);
									root->color = root->right->color;
									root->left->color = root->right->color = RED;
								}
								if(root->left->right->color == BLACK) {
									*grow = root->color == RED ? -1 : 0;
									root = Rebuild_LR(root);
									root->color = root->right->color;
									root->left->color = root->right->color = RED;
								}
							} else if(!(root->left->left) && !(root->left->right)) {
								root->left->color = BLACK;
								if(root->color == RED) *grow = -1;
								else { root->color = RED; *grow = 0; }
							} else if(!(root->left->left)) {
								*grow = root->color == RED ? -1 : 0;
								root = Rebuild_LR(root);
								root->color = root->right->color;
								root->left->color = root->right->color = RED;
							} else if(!(root->left->right)) {
								*grow = root->color == RED ? -1 : 0;
								root = Rebuild_LL(root);
								root->color = root->right->color;
								root->left->color = root->right->color = RED;
							}
					}
				}
			}
		}
		return root;
	}
}

template <class Ti_Type>
void Ti_RBTree<Ti_Type>::Ti_Show(Ti_TreeNode<Ti_Type> *position, int level, Ti_Type *x) {
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
	if(position->color) {
		printf("\033[30m");
		printf("\033[47m");
		printf("\033[01m");
		cout << "|-[";
	} else {
		printf("\033[31m");
		printf("\033[47m");
		printf("\033[01m");
		cout << "|-(";
	}
	cout.width(2);

	if(position->color) cout << position->value << "]|\033[00m" << endl;
	else cout << position->value << ")|\033[00m" << endl;


	x[level] = 1;
	Ti_Show(position->left, level + 1, x);
	x[level] = 0;
}

template <class Ti_Type>
void Ti_RBTree<Ti_Type>::Ti_Show() {
	int N = size(root);
	Ti_Type *x = new Ti_Type[N];
	for(int i = 0; i < N; i++) x[i] = 0;
	Ti_Show(root, 0, x);
	cout << endl;
}
