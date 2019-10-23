// (c) Tivole

#include "Ti_DynamicArray.hpp"
#include <iostream>
#include <ctime>

using namespace std;


void Test_1();
void Test_2();

int main() {

    srand(time(NULL));
    Test_1();
    Test_2();

    return 0;
}

void Test_1() {
    cout << "\n\n\t\t\t\t\t\tTEST 1\n\n";
    unsigned int i;
    double value;
    DArray A;

    for (i = 0; i < 8; i++) {
        A.pushback(rand() % 50);
    }

    cout << "The size of DArray is = " << A.size() << endl;
    cout << "The capacity of DArray is = " << A.get_capacity() << endl;
    cout << "The Dynamic Array: {";
    for(i = 0; i < A.size(); i++) {
        cout << A[i] << ", ";
    }
    cout << "}\n";

    for(i = 10; i < 19; i++) {
       A.pushback(rand() % 50);
    }

    cout << "\n\n";

    cout << "The size of DArray is = " << A.size() << endl;
    cout << "The capacity of DArray is = " << A.get_capacity() << endl;
    cout << "The Dynamic Array: {";
    for(i = 0; i < A.size(); i++) {
        cout << A[i] << ", ";
    }
    cout << "}\n";

    cout << "\n\n";

    for(i = 0; i < 6; i++) {
       A.pop_back(value);
    }

    cout << "\n\n";

    cout << "The size of DArray is = " << A.size() << endl;
    cout << "The capacity of DArray is = " << A.get_capacity() << endl;
    cout << "The Dynamic Array: {";
    for(i = 0; i < A.size(); i++) {
        cout << A[i] << ", ";
    }
    cout << "}\n";

    cout << "\n\n";
}

void Test_2() {
    cout << "\n\n\t\t\t\t\t\tTEST 2\n\n";
    unsigned int i;
    DArray B;


    B.pushback(7);
    for (i = 0; i < 30; i++) {
        B.pushback(rand() % 50);
    }

    cout << "The size of DArray is = " << B.size() << endl;
    cout << "The capacity of DArray is = " << B.get_capacity() << endl;
    cout << "The Dynamic Array: {";
    for(i = 0; i < B.size(); i++) {
        cout << B[i] << ", ";
    }
    cout << "}\n";

    cout << "\n\n";

    cout << "Looking for \"7\"\n";
    B.search(7);

    B.sort();

    cout << "\nAfter sorting: \n";

    cout << "The Dynamic Array: {";
    for(i = 0; i < B.size(); i++) {
        cout << B[i] << ", ";
    }
    cout << "}\n";

    cout << "\n\n";

    cout << "Looking for \"7\"\n";
    B.search(7);

    cout << "\n\n";
}
