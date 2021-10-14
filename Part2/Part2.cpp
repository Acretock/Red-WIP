#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class SimpleVector
{
public:
	SimpleVector() {
		data = nullptr;
		end_ = nullptr;
	}
	explicit SimpleVector(size_t size) {
		data = new T[size];
		end_ = data + size;

	}

	~SimpleVector() {
		cout << "no error 1";
		//delete[] data;
		delete end_;
		cout << "no error 2";
	}
	T& operator[](size_t index) {
		return *(data + index);
	}
	T& operator[](size_t index) const { return *(data + index); }
	T* begin() { return data; }
	T* end() { return end_; }
	T* begin() const { return data; }
	T* end() const { return end_; }
	size_t Size() const { return size; }
	size_t Capacity() const { return end_ - data; }
	void PushBack(const T& value) {
		if (Capacity() == 0) {
			unique_ptr<T*> tmp = new T[1u];
			tmp = data;
			delete[] data;
			data = new T[1u];
			end_ = data + 1u;
		} else if (Capacity() == Size()) {
			auto newSize = Capacity() * 2;
			//T* tmp = data;
			T* tmp = new T[newSize];
			//delete[] data;
			tmp = data;
			data = tmp;
			end_ = data + newSize;
		}
		*(data + size) = value;
		auto tmp = *(data + size);
		tmp++;
		size++;
	}

private:
	T* data;
	T* end_;
	size_t size = 0;

};

	int main() {
		SimpleVector<int> vector{};

		vector.PushBack(123);
		cout << vector.Capacity() << ' ' << vector.Size() << endl;
		vector.PushBack(333);
		cout << vector.Capacity() << ' ' << vector.Size() << endl;
		vector.PushBack(444);
		cout << vector.Capacity() << ' ' << vector.Size() << endl;
		vector.PushBack(434);
		cout << vector.Capacity() << ' ' << vector.Size() << endl;
		vector.PushBack(44);
		cout << vector.Capacity() << ' ' << vector.Size() << endl;

		cout << "no error    " <<  vector[0] << ' ' << vector[1] << ' ' << vector[2] << ' ' << vector[3] << ' ' << vector[4];

		return 0;
	}
