// (c) Tivole

#include <iostream>
using namespace std;

class Ti_ListElement {
	int value;
	Ti_ListElement *prev, *next;
	Ti_ListElement(int x = 0) {
		value = x;
		next = NULL;
		prev = NULL;
	}
	friend class Ti_List;
};

class Ti_List {
	Ti_ListElement *element;
public:
	Ti_List() {
		element = NULL;
	}
	~Ti_List();
	Ti_List(const Ti_List &y);
	void add_next(int);
	void add_prev(int);
	void step_next();
	void step_prev();
	void remove_this(int);
	void show();
};

Ti_List::~Ti_List() {
	if(element == NULL) return;
	else {
		Ti_ListElement *A;
		A = element->next;
		while(A != element) {
			A = A->next;
			delete A->prev;
		}
		delete element;
		element = NULL;
		A = NULL;
	}
}

Ti_List::Ti_List(const Ti_List &y) {
	if (y.element == NULL) {
		element = NULL;
		return;
	}
	Ti_ListElement *A, *B, *C;
	element = new Ti_ListElement(y.element->value);
	C = element;
	for (A = y.element->next; A != y.element; A = A->next) {
		B = new Ti_ListElement(A->value);
		B->prev = C;
		C->next = B;
		C = C->next;
	}
	B->next = element;
	C->prev = B;
}

void Ti_List::add_prev(int x) {
	if(element == NULL) {
		element = new Ti_ListElement(x);
		element->prev = element;
		element->next = element;
		return;
	}else {
		Ti_ListElement *A;
		A = new Ti_ListElement(x);
		A->next = element;
		A->prev = element->prev;
		element->prev->next = A;
		element->prev = A;
	}
}

void Ti_List::add_next(int x) {
	if(element == NULL) {
		element = new Ti_ListElement(x);
		element->prev = element;
		element->next = element;
		return;
	}else {
		Ti_ListElement *A;
		A = new Ti_ListElement(x);
		A->next = element->next;
		A->prev = element;
		element->next->prev = A;
		element->next = A;
	}
}

void Ti_List::step_next() {
	if(element != NULL) element = element->next;
}

void Ti_List::step_prev() {
	if(element != NULL) element = element->prev;
}

void Ti_List::remove_this(int bin) {
	if(element == NULL) return;
	else if(element->next == element) {
		delete element;
		element = NULL;
		return;
	}else {
		element->prev->next = element->next;
		element->next->prev = element->prev;
		delete element;
		if (bin >= 0) element = element->next;
		else element = element->prev;
	}
}

void Ti_List::show() {
	if(element == NULL) cout << " > The List is empty!" << endl << endl;
	else {
		Ti_ListElement *A;
		A = element->next;
		cout << " > " << element->value << " ";
		while (A != element) {
			cout << A->value << " ";
			A = A->next;
		}
		cout << endl << endl;
	}
}
