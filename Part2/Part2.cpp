#include <iostream>

using namespace std;

template<typename T>
class SimpleVector
{
public:
	SimpleVector() = default;
	explicit SimpleVector(size_t size) {
		data = new T[size];
		end_ = data + size;
	}

	~SimpleVector() {
		delete[] data;
		delete end;
	}
	T& operator[](size_t index) {
		return data[index];
	}
	T& operator[](size_t index) const { return data[index]; }
	T* begin() { return data; }
	T* end() { return end_; }
	T* begin() const { return data; }
	T* end() const { return end_; }
	size_t Size() const { return size; }
	size_t Capacity() const { return end() - begin(); }
	void PushBack(const T& value) {
		if (Capacity() == 0) {
			delete[] data;
			delete end;
			size++;
			data = new T[size];
			end_ = data + size;
		} else if (Capacity() == Size()) {
			auto newSize = Capacity() * 2;
			T* tmp = new T[newSize];
			tmp = data;
			delete[] data;
			data = tmp;
			delete[] tmp;
			end_ = data + newSize;
		}
		*(data + size) = value;
	}

private:
	T* data;
	T* end_;
	size_t size = 0;

};

	int main() {

		return 0;
	}
