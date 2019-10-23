// (c) Tivole

#include <iostream>
#include "Ti_BTree.hpp"

using namespace std;

void Test_1();
void Test_2();

int main() {
	getchar();
	Test_1();
	getchar();
	system("clear");

	Test_2();
	getchar();
	system("clear");

	return 0;
}

void Test_1() {
	Ti_BTree BT;
	int i, j, sizeb;
	int b[] = {1, 5, 9, 13, 17, 21, 25, 29, 2, 6, 10, 14, 18, 22, 26, 30};
	sizeb = sizeof(b) / sizeof(int);

	for(i = 0; i < sizeb; i++) {
		cout << "Inserting " << b[i] << ":\n\n";
		BT.insert(b[i]);
		BT.display();
		for(j = 0; j < 80; j++) cout <<"- ";
		cout << endl;
	}
}

void Test_2() {
	Ti_BTree BT;
	int i, j, sizea, sizeb;
	int b[] = {1, 5, 9, 13, 17, 21, 25, 29, 2, 6, 10, 14, 18, 22, 26, 30, 3,4,7,8,11,12,31,32,33,34};
	int a[] = {22, 13, 30, 25, 14,1,2,4,5};
	sizeb = sizeof(b) / sizeof(int);
	sizea = sizeof(a) / sizeof(int);

	for(i = 0; i < sizeb; i++) {
		BT.insert(b[i]);
	}
	cout << "BTree:\n\n";
	BT.display();

	for(i = 0; i < sizea; i++) {
		cout << "Deleting " << a[i] << ":\n\n";
		BT.DelNode(a[i]);
		BT.display();
		for(j = 0; j < 80; j++) cout <<"- ";
		cout << endl;
	}


}
