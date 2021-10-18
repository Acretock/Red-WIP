#include <iostream>
#include <algorithm>
#include "test_runner.h"
using namespace std;

template<typename T>
class SimpleVector
{
public:
	SimpleVector() {
		data = nullptr;
		end_ = data;
	}
	explicit SimpleVector(size_t size) {
		data = new T[size];
		end_ = data + size;
		capacity = size;
	}

	~SimpleVector() {
		delete[] data;
	}
	T& operator[](size_t index) { return *(data + index); }
	T& operator[](size_t index) const { return *(data + index); }
	T* begin() { return data; }
	T* end() { return end_; }
	T* begin() const { return data; }
	T* end() const { return end_; }
	size_t Size() const { return size; }
	size_t Capacity() const { return capacity; }
	void PushBack(const T& value) {
		if (Capacity() == 0) {
			data = new T[1];
			data[0] = value;
			end_ = data + 1;
			size++;
			capacity++;
		}
		else if (Capacity() == Size()) {
			auto newSize = Capacity() * 2;
			capacity = newSize;
			T* tmp = new T[newSize];
			for (auto i = 0; i < size; i++) {
				tmp[i] = data[i];
			}
			delete[] data;
			data = tmp;
			*(data + size) = value;
			size++;
			end_ = data + size;
		}
		else {
			*(data + size) = value;
			size++;
			end_ = data + size;
		}
	}

private:
	T* data;
	T* end_;
	size_t size = 0;
	size_t capacity = 0;

};
void TestConstruction() {
	SimpleVector<int> empty;
	ASSERT_EQUAL(empty.Size(), 0u);
	ASSERT_EQUAL(empty.Capacity(), 0u);
	ASSERT(empty.begin() == empty.end());

	SimpleVector<string> five_strings(5);
	ASSERT_EQUAL(five_strings.Capacity(), 5u);
	ASSERT(five_strings.Size() <= five_strings.Capacity());
	for (auto& item : five_strings) {
		ASSERT(item.empty());
	}
	five_strings[2] = "Hello";
	ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() {
	SimpleVector<int> v;
	for (int i = 10; i >= 1; --i) {
		v.PushBack(i);
		ASSERT(v.Size() <= v.Capacity());
	}
	cout << v.Size() << ' ' << v.Capacity();
	sort(begin(v), end(v));

	const vector<int> expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	ASSERT_EQUAL(v.Size(), expected.size());
	ASSERT(equal(begin(v), end(v), begin(expected)));
}
	int main() {

		TestRunner tr;
		RUN_TEST(tr, TestConstruction);
		RUN_TEST(tr, TestPushBack);

		SimpleVector<int> vector{};
		cout << vector.Capacity() << ' ' << vector.Size() << endl;
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

		cout << "no error    " << vector[0] << ' ' << vector[1] << ' ' << vector[2] << ' ' << vector[3] << ' ' << vector[4] << endl;

		SimpleVector<int> vector3{3};
		cout << vector3.Capacity() << ' ' << vector3.Size() << endl;
		vector3.PushBack(123);
		cout << vector3.Capacity() << ' ' << vector3.Size() << endl;
		vector3.PushBack(123);
		cout << vector3.Capacity() << ' ' << vector3.Size() << endl;
		vector3.PushBack(333);
		cout << vector3.Capacity() << ' ' << vector3.Size() << endl;
		vector3.PushBack(111);
		cout << vector3.Capacity() << ' ' << vector3.Size() << endl;
		vector3.PushBack(1);
		cout << vector3.Capacity() << ' ' << vector3.Size() << endl;

		cout << "no error    " << vector3[0] << ' ' << vector3[1] << ' ' << vector3[2] << ' ' << vector3[3] << ' ' << vector3[4] << endl;
		return 0;
	}
