#include <iostream>
#include <deque>

using namespace std;

template <class T>
class ObjectPool {
public:
	T* Allocate(const T& newData) {
		if (isDeallocated) {
			(allocated + size) = deallocated;
			allocatedEnd = allocated + sizeAlloc;
			sizeAlloc++;
			return allocatedEnd;
		}
		else {
			(allocated + sizeAlloc) = &newData;
			allocatedEnd = allocated + sizeAlloc;
			sizeAlloc++;
			return allocatedEnd;
		}
	}

	T* TryAllocate() {
		if (isDeallocated) {
			allocated + size = deallocated;
			allocatedEnd = allocated + sizeAlloc;
			sizeAlloc++;
			return allocatedEnd;
		}
		else {
			return nullptr;
		}
	}

	void Deallocate(T* object) {

	}
	ObjectPool() {
		allocated = new[] T;
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
	bool isDeallocated = false;
};

int main() {

}
