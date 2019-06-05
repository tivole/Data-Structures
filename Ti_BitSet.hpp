// (c) Tivole

#include <iostream>

using namespace std;

typedef unsigned int WORD;

class Ti_BitSet {
	int minElem, maxElem, numWords;
	WORD *elems;
public:
	Ti_BitSet(int min = 0, int max = 16);
	Ti_BitSet(const Ti_BitSet & s);
	~Ti_BitSet() { delete[] elems; }
	bool has(int n) const;
	Ti_BitSet & operator |= (int n);
	Ti_BitSet & operator |= (const Ti_BitSet & other);
	Ti_BitSet & operator &= (const Ti_BitSet & other);
	Ti_BitSet & operator -= (int n);
	Ti_BitSet & operator = (const Ti_BitSet &s);
	Ti_BitSet & inverse();
	Ti_BitSet & clear();
	bool isEmpty();
	friend ostream &operator << (ostream &stream, const Ti_BitSet &s);
};

// Конструктор
Ti_BitSet::Ti_BitSet (int min, int max) {
	if (min > max) {
		minElem = max;
		maxElem = min;
	} else {
		minElem = min;
		maxElem = max;
	}
	int num = maxElem - minElem + 1;
	numWords = (num + 15) >> 4;
	elems = new WORD [numWords];
	for (int i = 0; i < numWords; i++) elems [i] = 0;
}

// Конструктор копирования
Ti_BitSet::Ti_BitSet(const Ti_BitSet & s) {
	minElem = s.minElem;
	maxElem = s.maxElem;
	elems = new WORD[numWords = s.numWords];
	for (int i = 0; i < numWords; i++) elems [i] = s.elems[i];
}

// Проверка принадлежности элемента множеству
bool Ti_BitSet::has(int n) const {
	if (n > maxElem || n < minElem) return false;
	int bit = n - minElem;
	return (elems[bit >> 4] & (1 << (bit & 15))) != 0;
}

// Добавление элемента в множество
Ti_BitSet & Ti_BitSet::operator |= (int n) {
	if (n <= maxElem && n >= minElem) {
		int bit = n - minElem;
		elems [bit >> 4] |= (1 << (bit & 15));
	} else {
		cout << "Cannot add an element: it is out of range" << endl;
	}
	return *this;
}

// Добавление элементов другого множества в данное (объединение)
Ti_BitSet & Ti_BitSet::operator |= (const Ti_BitSet & other) {
	if (other.minElem != minElem || other .maxElem != maxElem) {
		cout << "Ti_BitSets incomparable" << endl;
	}
	for (int i = 0; i < numWords; i++) elems [i] |= other.elems[i];
	return *this;
}

// Пересечение множества с другим множеством
Ti_BitSet & Ti_BitSet:: operator &= (const Ti_BitSet & other) {
	if (other.minElem != minElem || other.maxElem != maxElem) {
		cout << "Ti_BitSets incomparable" << endl;
	}
	for (int i = 0; i < numWords; i++) elems [i] &= other.elems[i];
	return *this;
}

// Удаление элемента из множества
Ti_BitSet & Ti_BitSet::operator -= (int n) {
	if (n <= maxElem && n >= minElem) {
		int bit = n - minElem;
		elems[bit >> 4] &= ~(1 << (bit & 15));
	}
	return *this;
}

// Обращение (нахождение дополнения) множества
Ti_BitSet & Ti_BitSet::inverse() {
	for(int i = minElem; i <= maxElem; i++)  {
		int bit = i - minElem;
		elems[bit >> 4] = has(i) ? elems[bit >> 4] & ~(1 << (bit &15)) : elems[bit >> 4] | (1 << (bit &15));
	}
	return *this;
}

// Очистить множество
Ti_BitSet & Ti_BitSet::clear() {
	for (int i = 0; i < numWords; i++) elems [i] = 0;
	return *this;
}

// Is Emtpty ?
bool Ti_BitSet::isEmpty() {
	for (int i = 0; i < numWords; i++) if(elems[i]) return false;
	return true;
}

// Оператор присваивания
Ti_BitSet & Ti_BitSet::operator = (const Ti_BitSet &s) {
	minElem = s.minElem;
	maxElem = s.maxElem;
	delete [] elems;
	elems = new WORD[numWords = s.numWords];
	for (int i = 0; i < numWords; i++) elems [i] = s.elems[i];
	return *this;
}

// Вывод на экран
ostream & operator << (ostream &stream, const Ti_BitSet &s) {
	stream << "{ ";
	int i;
	for(i = s.minElem; i <= s.maxElem; i++) {
		if(s.has(i)) stream << i << ", ";
	}
	stream << " }";
	stream << endl;
	return stream;
}
