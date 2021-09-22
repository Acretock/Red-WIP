#include <iostream>
#include <deque>
#include <exception>
#include <algorithm>
#include <limits>
#include <tuple>

using namespace std;

template <class T>
class ObjectPool {
public:
	T* Allocate(const T& newData) {
		if (checkDealloc(&newData)) {
			addDeallocated(newData);
			return &(allocated[sizeAlloc - 1]);
		}
		else {
			addNewData(newData);
			return &(allocated[sizeAlloc - 1]);
		}
	}

	T* TryAllocate() {
		if (checkDealloc()) {
			addDeallocated();
			return &(allocated[sizeAlloc - 1]);
		}
		else {
			return nullptr;
		}
	}

	void Deallocate(const T* object) {
		auto [data, num] = find(allocated, allocatedEnd, *object);
		if (/*in alloc*/ data != allocatedEnd) {
			/*add into dealloc*/
			deallocated[sizeDealloc] = *data;
			sizeDealloc++; 
			allocated[num] = T();
		}
		else {
			throw invalid_argument("not in allocated memory");
		}
	}
	ObjectPool() {
		allocated = new T[100];
		deallocated = new T[100];
		allocatedEnd = allocated + 100;
		deallocatedEnd = deallocated + 100;
	}
	~ObjectPool() {
		delete[] allocated;
		delete[] deallocated;
	}

private:
	T* allocated;
	T* allocatedEnd;
	size_t sizeAlloc = 0;

	T* deallocated; // no need to clear in allocate 
	T* deallocatedEnd;
	size_t sizeDealloc = 0;

	void addDeallocated(T object) {
		*(allocated + sizeAlloc) = *deallocated;
		sizeAlloc++;
	}

	void addNewData(T newData) {
		T* data = &newData;
		*(allocated + sizeAlloc) = *data;
		sizeAlloc++;
	}

	bool checkDealloc() {
		return sizeDealloc > 0;
	}

	bool checkDealloc(const T* data) {
		auto [data2, num] = find(allocated, allocatedEnd, *data);
		return data2 == deallocatedEnd;
	}

	tuple<T*,size_t> find(T* first, T* last, const T& value) {
		T* data1 = first;
		T* data2 = last;
		size_t count = 0;
			for (; data1 != data2; ++data1) {
				if (*data1 == value) {
					return { data1, count };
				}
				count++;
			}
			return { data2, count };
	}
};

int main() {
	ObjectPool<int> help_me;
	int* t;
	int* y;
	int* x;
	t = help_me.Allocate(123);
	y = help_me.Allocate(312);
	x = help_me.Allocate(333);
	int* z;
	z = help_me.Allocate(515);
	help_me.Deallocate(z);
	help_me.Deallocate(t);
	int* h = help_me.Allocate(123);
	int* q = help_me.Allocate(555);
	cout << *t << " " << *y << " " << *x << " " << *z << " " << *h << " " << *q << endl;
	return 0;
}
