// (c) Tivole

#include <iostream>
#include "Ti_BinaryTree.hpp"
using namespace std;

void Test_1();
void Test_2();
void Test_3();

int main() {

	getchar();
	Test_1(); // Adding elements and Show Functions
	getchar();
	system("clear");

	Test_2(); // Deleting elements
	getchar();
	system("clear");

	return 0;
}

void Test_1() {

	Ti_Tree<int> A;

	int b[7] = {5, 5, 5, 3, 8, 7, 2}, x;
	for(int i = 0; i < 7; i++) A.AddElement(b[i]);

	cout << "\t\tTi_Show:\n\n";
	A.Ti_Show();

	cout << "\n\t\tShow LR:\n\n";
	A.ShowLR();

	cout << "\n\t\tShow DU\n\n";
	A.ShowDU();

	cout << "\n\t\tShow UD:\n\n";
	A.ShowUD();

	A.RootValue(&x);
	cout << "\nRoot value is: " << x << endl;

}

void Test_2() {

	Ti_Tree<int> A;

	int b[] = {4};
	int sizeb = sizeof(b) / sizeof(int);
	for(int i = 0; i < sizeb; i++) A.AddElement(b[i]);

	cout << "\t\tTi_Show:\n\n";
	A.Ti_Show();

	cout << "\n--------------------------\n\n";
	A.DeleteElement(4);
	cout << endl;
	A.Ti_Show();

	cout << "\n--------------------------\n\n";
	A.DeleteElement(4);
	cout << endl;
	A.Ti_Show();

}
