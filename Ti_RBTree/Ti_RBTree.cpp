// (c) Tivole

#include <iostream>
#include "Ti_RBTree.hpp"
using namespace std;

void Test_1();
void Test_2();

int main(){

	getchar();

	Test_1(); // Adding element and show function
	getchar();
	system("clear");

	Test_2(); // Deleting elements
	getchar();
	system("clear");

	return 0;
}

void Test_1() {
	cout << "\t\t\t\tTest 1 \n" << endl;
	int i, j, element;
	Ti_RBTree<int> A;

	A.AddElement(21);
	A.AddElement(27);
	A.AddElement(23);
	A.AddElement(31);

	for (i = 0; i < 20; i++) {

		if (i%2) element = i;
		else element = 20 - i;

		A.AddElement(element);

		cout << endl;
		for(j = 0; j < 80; j++) cout << "-";
		cout << endl;
		cout << ">>>>>>>>> Adding " << element << endl;

		cout << endl << " Up Down: ";
		A.ShowUD();
		cout << endl << " Left Right: ";
		A.ShowLR();
		cout << endl << " Down Up: ";
		A.ShowDU();

		cout << endl << endl;
		A.Ti_Show();
	}
	cout << endl << endl;
}

void Test_2() {

	Ti_RBTree<int> A;

	int i, b[14] = {5, 4, 6, 13, 10, 15, 3, 8, 7, 17, 20, 2, 1, 9};
	for(i = 0; i < 14; i++) A.AddElement(b[i]);

	cout << "\t\t\tTest 2:\n\n";
	A.Ti_Show();

	for(i = 0; i < 80; i++) cout << "-";
	cout << "\n\n>>>>>>>> Deleting " << 8 << endl;
	A.DeleteElement(8);
	cout << endl;
	A.Ti_Show();

	for(i = 0; i < 80; i++) cout << "-";
	cout << "\n\n>>>>>>>> Deleting " << 7 << endl;
	A.DeleteElement(7);
	cout << endl;
	A.Ti_Show();

	for(i = 0; i < 80; i++) cout << "-";
	cout << "\n\n>>>>>>>> Deleting " << 6 << endl;
	A.DeleteElement(6);
	cout << endl;
	A.Ti_Show();

	for(i = 0; i < 80; i++) cout << "-";
	cout << "\n\n>>>>>>>> Deleting " << 5 << endl;
	A.DeleteElement(5);
	cout << endl;
	A.Ti_Show();

	for(i = 0; i < 80; i++) cout << "-";
	cout << "\n\n>>>>>>>> Deleting " << 4 << endl;
	A.DeleteElement(4);
	cout << endl;
	A.Ti_Show();

	for(i = 0; i < 80; i++) cout << "-";
	cout << "\n\n>>>>>>>> Deleting " << 3 << endl;
	A.DeleteElement(3);
	cout << endl;
	A.Ti_Show();

	for(i = 0; i < 80; i++) cout << "-";
	cout << "\n\n>>>>>>>> Deleting " << 10 << endl;
	A.DeleteElement(10);
	cout << endl;
	A.Ti_Show();
}
