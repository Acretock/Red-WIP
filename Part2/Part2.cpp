#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void swap(T* a, T* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

template<typename T>
void sortPointers(vector<T*>& pointers) {

}

// копирование одного объекта только один раз
// могут пересекаться [src, src + size)
// те которые не пересекаются не изменять
template<typename T>
void reverseCopy(T* src, size_t size, T* dst) {

}

int main() {




	return 0;
}