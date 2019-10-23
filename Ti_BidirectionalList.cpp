// (c) Tivole

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Ti_List.hpp"
using namespace std;

void Test_1();
void Test_2();
void Test_3();

int main() {

	getchar();
	Test_1();  // Add and Remove

	getchar();
	system("clear");

	Test_2();  // Constructor and Destructor

	getchar();
	system("clear");

	Test_3();  // Constructor Copy

	getchar();
	system("clear");

	return 0;
}

void Test_1() {
	cout << "\t\t\t\t Test 1 \n";

	Ti_List A;
	int i;

	A.add_next(73);
	for(i = 0; i <= 10000; i++) {
		A.add_next(i);
		A.add_prev(i);
		A.remove_this(pow(-1, i));
	}
	A.show();
}

void Test_2() {
	cout << "\t\t\t\t Test 2 \n";

	Ti_List *A;
	int i, j;

	for (i = 0; i <= 1000 ; i++) {
		A = new Ti_List;
		for(j = 1; j <= 50; j++) A->add_next(j);
		if(i == 1000) {
			A->step_next();
			break;
		}
		delete A;
	}
	A->show();
}

void Test_3() {
	cout << "\t\t\t\t Test 3 \n";

	Ti_List A;
	int i;

	for (i = 0; i < 24; i++) A.add_prev(i%6);

	cout << "  List A:" << endl;
	A.show();

	Ti_List B = A;

	cout << "  List B:" << endl;
	B.show();
}
