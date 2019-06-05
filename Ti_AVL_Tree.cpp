// (c) Tivole

#include <iostream>
#include "Ti_AVL_Tree.hpp"
using namespace std;

void Test_1();
void Test_2();

int main() {

	getchar();

	Test_1(); // Adding Elements and show Tree
	getchar();
	system("clear");

	Test_2(); // Adding and deleting elements
	getchar();
	system("clear");

	return 0;
}

void Test_1() {
	cout << "\t\t\t\tTest 1 \n" << endl;
	int i, j, grow = 0, element;
	Ti_AVL_Tree avl;
	for (i = 0; i < 20; i++) {

		if (i%2) element = i;
		else element = 20 - i;

		avl.root = avl.AddElement(element, avl.root, &grow);

		cout << endl;
		for(j = 0; j < 80; j++) cout << "-";
		cout << endl;
		cout << "Adding " << element;

		cout << endl << " Up Down: ";
		avl.UpDown(avl.root);
		cout << endl << " Left Right: ";
		avl.LeftRight(avl.root);
		cout << endl << " Down Up: ";
		avl.DownUp(avl.root);

		avl.Ti_Show();
	}
	cout << endl << endl;
}

void Test_2() {
	cout << "\t\t\t\tTest 2 " << endl;
	Ti_AVL_Tree avl;
	int i, grow = 0;
	for(i = 0; i < 100000; i++) {
		avl.root = avl.AddElement(i, avl.root, &grow);
		avl.root = avl.AddElement(i, avl.root, &grow);

	}
	for(i = 20; i < 100000; i++) {
		avl.root = avl.DeleteElement(i, avl.root, &grow);
	}
	cout << endl;
	avl.LeftRight(avl.root);
	avl.Ti_Show();
}
