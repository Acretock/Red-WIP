#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void Swap(T* a, T* b) {
	T tmp = *a;
	*a = *b;
	*b = tmp;
}
using namespace std;

template<typename T>
int partition(vector<T*>& ptrs, int low, int high)
{
    int pivot = *ptrs[high]; // pivot 
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot 
        if (*ptrs[j] < pivot)
        {
            i++; // increment index of smaller element 
            Swap(ptrs[i], ptrs[j]);
        }
    }
    Swap(ptrs[i + 1], ptrs[high]);
    return (i + 1);
}

template<typename T>
void QuickSort(vector<T*>& ptrs, int low, int high)
{
    if (low < high)
    {
        int pi = partition(ptrs, low, high);

        quickSort(ptrs, low, pi - 1);
        quickSort(ptrs, pi + 1, high);
    }
}

template<typename T>
void sortPointers(vector<T*>& ptrs) {
    QuickSort(ptrs, 0, ptrs.size() - 1);
}

// копирование одного объекта только один раз
// могут пересекаться [src, src + size)
// те которые не пересекаются не изменять
template<typename T>
bool isCross(T* src, std::size_t size, T* dst) {
    auto res = abs(src - dst);
    return res < size;
}

template<typename T>
bool isLeftCross(T* src, std::size_t size, T* dst) {
    auto res = (src - dst);
    return (src - dst) > 0;
}
template<typename T>
size_t isLeftCross2(T* src, T* dst) {
    int res = (src - dst);
    return res;
}

template<typename T> /*пока не внутри копируем, если внутри то меняем*/
void endStart(T* src, std::size_t size, T* dst, size_t raz) {

    int i = 0;

    for (int c = 0; c < raz; c++) {
        auto j = size - i - 1;
        dst[i] = src[j];
        i++;
    }
    i--;
    for (int c = raz; c < size; c++) {
        auto j = size - i - 1;
        Swap(&src[j], &dst[i]);
        i++;
    }
}

template<typename T> /*пока не внутри копируем, если внутри то меняем*/
void startEnd(T* src, size_t size, T* dst, size_t raz) {

    int i = 0;

    for (int c = 0; c < raz; c++) {
        auto j = size - i - 1;
        dst[j] = src[i];
        i++;
    }
    i--;
    for (int c = raz; c < size; c++) {
        auto j = size - i - 1;
        Swap(&src[i], &dst[j]);
        i++;
    }
}

template<typename T>
void reverseCopy(T* src, size_t size, T* dst) {
    if (isCross(src, size, dst)) {
        if (!isLeftCross(src, size, dst)) {
            startEnd(src, size, dst, abs(src-dst));
        } else {
            endStart(src, size, dst, abs(src - dst));
        }
    } else {
        for (auto i = 0; i < size; i++) {
            auto j = size - i - 1;
            *(dst + j) = *(src + i);
        }
    }
}



int main() {
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    int* pa = new int[8];
    int* pb = pa + 1;
    int* pc = pa + 2;
    int* pd = pa + 3;
    int* pe = pa + 4;
    pa[3] = 15;
    pa[4] = 7;
    pa[5] = 11;
    pa[6] = 4;
    pa[7] = 99;
    /*
    *a = 12;
    *b = 5;
    *c = 7;
    *d = 1;
    *e = 3;
    */

    
    reverseCopy(pd, 5, pa);
    for (int i = 0; i < 8; i++) {
        cout << pa[i] << ' ';
    }
	return 0;
}
