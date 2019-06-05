// (c) Tivole

#include <iostream>
#include "Ti_BitSet.hpp"

using namespace std;

void Test_1();
void Test_2();
void Test_3();

int main() {

	Test_1(); // Adding and Deleting
	getchar();
	system("clear");

	Test_2(); // Intersection and Union
	getchar();
	system("clear");

	Test_3(); // Other functions
	getchar();
	system("clear");

	return 0;
}

void Test_1() {
	Ti_BitSet BS(-32, 32);
	int i;

	cout << "Adding:\n";
	for(i = 0; i < 15; i++) {
		cout << "+ (" << (i*2+1)*(i%2?-1:1) << ")" << endl;
		BS |= (i*2+1)*(i%2?-1:1);
		cout << BS << endl;
	}
	cout << "Deleting:\n";
	cout << BS << endl;
	for(i = 0; i < 15; i++) {
		cout << "- (" << (i*2 + 1) << ")" << endl;
		BS -= (2*i + 1);
		cout << BS << endl;
	}
}

void Test_2() {
	Ti_BitSet BS1(-16, 16), BS2(-16, 16);
	int i;

	for(i = 0; i < 8; i++) BS1 |= (i*2+1)*(i%2?-1:1);
	for(i = 0; i < 5; i++) BS2 |= (i*2)*(i%2?-1:1);
	BS2 |= 9;
	BS2 |= 11;

	cout << "BS1: " << BS1;
	cout << "BS2: " << BS2;
	cout << endl;

	cout << "\nBS1 & BS2:\n";
	BS2 &= BS1;
	cout << BS2;

	for(i = 0; i < 8; i++) BS1 |= (2*i + 1);
	for(i = 0; i < 5; i++) BS2 |= (2*i);
	BS2 |= 9;
	BS2 |= 11;

	cout << "\nBS1 | BS2:\n";
	BS2 |= BS1;
	cout << BS2;

}

void Test_3() {
	Ti_BitSet BS1(0, 16), BS2(0, 16);

	int i;
	for(i = 0; i < 5; i++) BS2 |= (2*i);
	BS2 |= 9;
	BS2 |= 11;

	cout << "BS1: " << BS1;
	cout << "BS2: " << BS2;
	cout << endl;

	cout << "Is empty BS1 ?\t" << BS1.isEmpty() << endl;
	cout << "Is empty BS2 ?\t" << BS2.isEmpty() << endl;

	cout << "\nInversions: " << endl;
	BS1.inverse();
	BS2.inverse();
	cout << "BS1: " << BS1;
	cout << "BS2: " << BS2;
	cout << endl;

	cout << "\nClear BS2:\n";
	BS2.clear();
	cout << "BS1: " << BS1;
	cout << "BS2: " << BS2;
	cout << endl;

}
