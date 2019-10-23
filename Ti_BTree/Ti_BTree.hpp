// (c) Tivole

#include <iostream>
#include <cstdlib>
using namespace std;

#define M 5

class Ti_BTreeNode{
	int n;
	int keys[M-1];
	Ti_BTreeNode *p[M];
	friend class Ti_BTree;
};

enum KeyStatus { Duplicate,SearchFailure,Success,InsertIt,LessKeys };

class Ti_BTree {

	Ti_BTreeNode *root=NULL;

	void display(Ti_BTreeNode *root, int);
	enum KeyStatus ins(Ti_BTreeNode *r, int x, int* y, Ti_BTreeNode** u);
	int searchPos(int x,int *key_arr, int n);
	enum KeyStatus del(Ti_BTreeNode *r, int x);

public:
	void search(int x);
	void insert(int key);
	void DelNode(int x);
	void display() { display(root, 0); cout << endl; }
};

void Ti_BTree::insert(int key) {
	Ti_BTreeNode *newnode;
	int upKey;
	enum KeyStatus value;
	value = ins(root, key, &upKey, &newnode);
	if (value == Duplicate) printf("Key already available\n");
	if (value == InsertIt) {
		Ti_BTreeNode *uproot = root;
		root=(Ti_BTreeNode*)malloc(sizeof(Ti_BTreeNode));
		root->n = 1;
		root->keys[0] = upKey;
		root->p[0] = uproot;
		root->p[1] = newnode;
	}
}

enum KeyStatus Ti_BTree::ins(Ti_BTreeNode *ptr, int key, int *upKey,Ti_BTreeNode **newnode) {
	Ti_BTreeNode *newPtr, *lastPtr;
	int pos, i, n,splitPos;
	int newKey, lastKey;
	enum KeyStatus value;
	if (ptr == NULL) {
		*newnode = NULL;
		*upKey = key;
		return InsertIt;
	}

	n = ptr->n;
	pos = searchPos(key, ptr->keys, n);
	if (pos < n && key == ptr->keys[pos]) return Duplicate;
	value = ins(ptr->p[pos], key, &newKey, &newPtr);
	if (value != InsertIt) return value;

	if (n < M - 1) {
		pos = searchPos(newKey, ptr->keys, n);

		for (i=n; i>pos; i--) {
			ptr->keys[i] = ptr->keys[i-1];
			ptr->p[i+1] = ptr->p[i];
		}
		ptr->keys[pos] = newKey;
		ptr->p[pos+1] = newPtr;
		++ptr->n;
		return Success;
	}

	if (pos == M - 1) {
		lastKey = newKey;
		lastPtr = newPtr;
	} else {
		lastKey = ptr->keys[M-2];
		lastPtr = ptr->p[M-1];
		for (i=M-2; i>pos; i--) {
			ptr->keys[i] = ptr->keys[i-1];
			ptr->p[i+1] = ptr->p[i];
		}
		ptr->keys[pos] = newKey;
		ptr->p[pos+1] = newPtr;
	}
	splitPos = (M - 1)/2;
	(*upKey) = ptr->keys[splitPos];

	(*newnode)=(Ti_BTreeNode*)malloc(sizeof(Ti_BTreeNode));
	ptr->n = splitPos;
	(*newnode)->n = M-1-splitPos;
	for (i=0; i < (*newnode)->n; i++)
	{
		(*newnode)->p[i] = ptr->p[i + splitPos + 1];
		if(i < (*newnode)->n - 1)
			(*newnode)->keys[i] = ptr->keys[i + splitPos + 1];
		else
			(*newnode)->keys[i] = lastKey;
	}
	(*newnode)->p[(*newnode)->n] = lastPtr;
	return InsertIt;
}

void Ti_BTree::display(Ti_BTreeNode *ptr, int blanks) {
	if (ptr) {
		int i;
		for(i=1;i<=blanks;i++)
			printf(" ");
		for (i=0; i < ptr->n; i++)
			printf("%d ",ptr->keys[i]);
		printf("\n");
		for (i=0; i <= ptr->n; i++)
			display(ptr->p[i], blanks+10);
	}
}

void Ti_BTree::search(int key) {
	int pos, i, n;
	Ti_BTreeNode *ptr = root;
	printf("Search path:\n");
	while (ptr) {
		n = ptr->n;
		for (i=0; i < ptr->n; i++) printf(" %d",ptr->keys[i]);
		printf("\n");
		pos = searchPos(key, ptr->keys, n);
		if (pos < n && key == ptr->keys[pos]) {
			printf("Key %d found in position %d of last dispalyed node\n",key,i);
			return;
		}
		ptr = ptr->p[pos];
	}
	printf("Key %d is not available\n",key);
}

int Ti_BTree::searchPos(int key, int *key_arr, int n) {
	int pos=0;
	while (pos < n && key > key_arr[pos]) pos++;
	return pos;
}

void Ti_BTree::DelNode(int key) {
	Ti_BTreeNode *uproot;
	enum KeyStatus value;
	value = del(root,key);
	if(value == SearchFailure) {
		 printf("Key %d is not available\n",key);
	} else if(value == LessKeys) {
				uproot = root;
		root = root->p[0];
		free(uproot);
	}
}

enum KeyStatus Ti_BTree::del(Ti_BTreeNode *ptr, int key) {
	int pos, i, pivot, n ,min;
	int *key_arr;
	enum KeyStatus value;
	Ti_BTreeNode **p,*lptr,*rptr;

	if (ptr == NULL) return SearchFailure;

	n=ptr->n;
	key_arr = ptr->keys;
	p = ptr->p;
	min = (M - 1)/2;

	pos = searchPos(key, key_arr, n);
	if (p[0] == NULL) {
		if (pos == n || key < key_arr[pos]) return SearchFailure;

		for (i=pos+1; i < n; i++) {
			key_arr[i-1] = key_arr[i];
			p[i] = p[i+1];
		}
		return  --ptr->n >= (ptr==root ? 1 : min) ? Success : LessKeys;
	}

	if (pos < n && key == key_arr[pos]) {
		Ti_BTreeNode *qp = p[pos], *qp1;
		int nkey;
		while(1) {
			nkey = qp->n;
			qp1 = qp->p[nkey];
			if (qp1 == NULL) break;
			qp = qp1;
		}
		key_arr[pos] = qp->keys[nkey-1];
		qp->keys[nkey - 1] = key;
	}
	value = del(p[pos], key);
	if (value != LessKeys) return value;

	if (pos > 0 && p[pos-1]->n > min) {
		pivot = pos - 1;
		lptr = p[pivot];
		rptr = p[pos];

		rptr->p[rptr->n + 1] = rptr->p[rptr->n];
		for (i=rptr->n; i>0; i--) {
			rptr->keys[i] = rptr->keys[i-1];
			rptr->p[i] = rptr->p[i-1];
		}
		rptr->n++;
		rptr->keys[0] = key_arr[pivot];
		rptr->p[0] = lptr->p[lptr->n];
		key_arr[pivot] = lptr->keys[--lptr->n];
		return Success;
	}
	if (pos<n && p[pos+1]->n > min) {
		pivot = pos;
		lptr = p[pivot];
		rptr = p[pivot+1];

		lptr->keys[lptr->n] = key_arr[pivot];
		lptr->p[lptr->n + 1] = rptr->p[0];
		key_arr[pivot] = rptr->keys[0];
		lptr->n++;
		rptr->n--;
		for (i=0; i < rptr->n; i++) {
			rptr->keys[i] = rptr->keys[i+1];
			rptr->p[i] = rptr->p[i+1];
		}
		rptr->p[rptr->n] = rptr->p[rptr->n + 1];
		return Success;
	}

	if(pos == n)
			pivot = pos-1;
	else
			pivot = pos;

	lptr = p[pivot];
	rptr = p[pivot+1];


	lptr->keys[lptr->n] = key_arr[pivot];
	lptr->p[lptr->n + 1] = rptr->p[0];
	for (i=0; i < rptr->n; i++) {
			lptr->keys[lptr->n + 1 + i] = rptr->keys[i];
			lptr->p[lptr->n + 2 + i] = rptr->p[i+1];
	}
	lptr->n = lptr->n + rptr->n +1;
	free(rptr);
	for (i=pos+1; i < n; i++) {
			key_arr[i-1] = key_arr[i];
			p[i] = p[i+1];
	}
	return  --ptr->n >= (ptr == root ? 1 : min) ? Success : LessKeys;
}
