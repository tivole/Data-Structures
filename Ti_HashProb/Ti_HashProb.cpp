// (c) Tivole

#include <iostream>
#include <ctime>

using namespace std;

int pls(int*, int, int, int*);
int mins(int*, int, int, int*);

void Test_1();
void Test_2();

int main() {

	Test_2();
	getchar();
	getchar();
	system("clear");

	Test_1();

	return 0;
}

void Test_1() {
	int n, i, value, kollixia = 0, k;
	char sgn;
	cout << " Enter the size of array: ";
	cin >> n;
	int array[n];
	cout << endl << " > ";
	for (i = 0; i < n; i++) {
	  array[i] = 0;
	  cout << array [i] << " ";
	}
	while (1) {
	start:
		cout << endl << endl << " ";
		cin >> sgn;
		cin >> value;
		switch (sgn) {
			case '+':
				k = pls(array, value, n, &kollixia);
				if(k == -1) cout << endl << " \t\t The number is not unsigned int! ";
				else if(k == -2) cout << endl << " \t\t There already is this number in array! ";
				else if(k == -3) cout << endl << " \t\t There is no place in array! ";
				break;
			case '-':
				k = mins(array, value, n, &kollixia);
				if(k == -1) cout << endl << " \t\t The number is not unsigned int! ";
				else if(k == -2) cout << endl << " \t\t There is no this number in this array! ";
				break;
			default:
				cout << " \t\t\t This operation is not available! ";
				goto start;
		}
		cout << endl << endl << " > ";
		for (i = 0; i < n; i++) cout << array [i] << " ";
		cout << endl << " The number of kolliziones is " << kollixia;
		kollixia = 0;
	}
}

void Test_2() {
	int i, d, koll, t[1000];
	double pls_k = 0, mins_k = 0, q, b;

	for(i = 0; i < 1000; i++) t[i]=0;

	cout<<" Enter the coefficient: ";

	error:
	cin >> q;

	if(q>=1 || q<=0) { cout<<" Enter another number q: "; goto error; }

	b = 1000*q;

	i = 0;

	srand(time(NULL));

	while (i < b) {
		d = rand() % 10000;
		i += pls(t, d, 1000, &koll);
	}

	for(i=0; i<1000000; i++) {
		koll=0;
		while( 1 != pls(t, rand()%10000, 1000, &koll) );
		pls_k += koll;
		koll=0;
		while( !(d = t[rand() % 1000]) ) ;
		mins(t, d, 1000, &koll);
		mins_k += koll;
	}

	cout << endl << endl;
	cout << " Kolliziones of plus => " << pls_k/1000000 << endl;
	cout << " Kolliziones of minus => " << mins_k/1000000 << endl;
	cout << " Whole kolliziones => " << (pls_k/1000000 + mins_k/1000000)  << endl;
	cout << " Extra actions => " << q / (1.0-q) << endl;
}

int pls(int *a, int x, int n, int *kollixia) {
	if(x <= 0) return -1;
	int i = x % n;
	while(a[i] != 0) {
		if(a[i] == x) return -2;
		(*kollixia)++;
		i = (i + 1) % n;
		if((*kollixia) >= n) return -3;
	}
	a[i] = x;
	return 1;
}

int mins(int *a, int x, int n, int *kollixia) {
	if(x <= 0) return -1;
	int i = x % n;
	while(a[i] != x) {
		if(a[i] == 0) return -2;
		i = (i + 1) % n;
		(*kollixia)++;
		if((*kollixia) >= (n)) return -2;
	}
	a[i] = 0;
	for(int j=(i+1)%n; a[j]!=0; j=(j+1)%n) {
		int z = a[j]%n;
		if((i-z+n) % n < (j-z+n) % n) {
			a[i] = a[j];
			i = j;
			a[i] = 0;
		}
		(*kollixia)++;
	}
	return 1;
}
