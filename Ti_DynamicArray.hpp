// (c) Tivole

#include <iostream>

using namespace std;

#define BASE_CAPACITY 5

class DArray {
private:
	double* defaultArray;
	unsigned int capacity = BASE_CAPACITY;
	unsigned int num_elements = 0;
    void quickSort(int, int);
    int binarySearch(int, int, int);

public:

    DArray();
	DArray(unsigned int);
	DArray(const DArray&);
	~DArray();

	void pushback(const double);
    void sort();
    bool search(double);
	double operator[](unsigned int);
	unsigned int size();
	unsigned int get_capacity();
	bool pop_back(double&);

};

bool DArray::search(double elem) {
    unsigned int i;
    int check;

    for(i = 1; i < num_elements; i++) {
        if(defaultArray[i] < defaultArray[i-1]) {
            break;
        }
    }
    if(i != num_elements) {
        cout << "(!) The array is not sorted for using binary search!\n";
        return false;
    }

    check = binarySearch(0, num_elements-1, elem);

    if(-1 == check) {
        cout << "(!) " << elem << " is not in array!\n";
        return false;
    }else {
        cout << elem << " is in the index = " << check << endl;
        return true;
    }

}

int DArray::binarySearch(int l, int r, int x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (defaultArray[mid] == x) return mid;
        if (defaultArray[mid] > x) return binarySearch(l, mid - 1, x);
        return binarySearch(mid + 1, r, x);
    }
    return -1;
}

void DArray::quickSort(int left, int right) {
      int i = left, j = right, pivot, tmp;
      pivot =  (defaultArray[left] + defaultArray[right])/2;
      while (i <= j) {
            while (defaultArray[i] < pivot) i++;
            while (defaultArray[j] > pivot) j--;
            if (i <= j) {
                  tmp = defaultArray[i];
                  defaultArray[i] = defaultArray[j];
                  defaultArray[j] = tmp;
                  i++;
                  j--;
            }
      }
      if (left < j) quickSort(left, j);
      if (right > i) quickSort(i, right);
}

void DArray::sort() {
    quickSort(0, num_elements-1);
}

DArray::DArray() {
    defaultArray = new double[capacity];
}

DArray::DArray(unsigned int elements) {
    capacity = elements;
    defaultArray = new double[capacity];
}

DArray::DArray(const DArray& otherclas) {
    capacity = otherclas.capacity;
    num_elements = otherclas.num_elements;
    defaultArray = new double[capacity];
    for (unsigned int i = 0; i < num_elements; i++) {
        defaultArray[i] = otherclas.defaultArray[i];
    }
}

DArray::~DArray() {
    delete[]defaultArray;
}

void DArray::pushback(const double item) {
    if (num_elements == capacity) {
        double* tempArray;
        capacity += BASE_CAPACITY;
        tempArray = new double[capacity];
        for (unsigned int i = 0; i < num_elements; i++) {
            tempArray[i] = defaultArray[i];
        }
        delete[] defaultArray;
        defaultArray = tempArray;
    }
    defaultArray[num_elements++] = item;
}

double DArray::operator[](unsigned int index) {
    if (index >= 0 && index < num_elements) {
        return defaultArray[index];
    } else {
        cout << "(!) Segmentation fault!\n";
        exit(1);
    }
}

bool DArray::pop_back(double& value) {
    if(num_elements > 0) {
        num_elements--;
        value = defaultArray[num_elements];
        if((capacity - BASE_CAPACITY) == num_elements) {
            double* tempArray;
            capacity -= BASE_CAPACITY;
            tempArray = new double[capacity];
            for (unsigned int i = 0; i < num_elements; i++) {
                tempArray[i] = defaultArray[i];
            }
            delete[] defaultArray;
            defaultArray = tempArray;
        }
        return true;
    } else {
        cout << "(!) There is no elements in array!\n";
        return false;
    }
}

unsigned int DArray::get_capacity() {
    return capacity;
}

unsigned int DArray::size(){
    return num_elements;
}
