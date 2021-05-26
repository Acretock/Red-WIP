#include <vector>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <iostream>
using namespace std;

template <typename T>
class Deque
{
public:
	Deque() : back(0), front(0) {};
	bool Empty() const {
		if (back.empty() && front.empty()) {
			return true;
		}
		return false;
	}

	size_t Size() const {
		return (back.size() + front.size());
	}

	T& operator[](size_t pos) {
		if (pos < front.size()) {
			return front[front.size() - pos - 1];
		}
		else {
			return back[pos - front.size()];
		}
	}

	const T& operator[](size_t pos) const {
		if (pos < front.size()) {
			return front[front.size() - pos - 1];
		}
		else {
			return back[pos - front.size()];
		}
	}

	const T& At(size_t pos) const {
		if (pos > (back.size() + front.size())) {
			throw out_of_range("");
		}
		if (pos < front.size()) {
			return front[front.size() - pos - 1];
		}
		else {
			return back[pos - front.size()];
		}
	}

	T& At(size_t pos) {
		if (pos > (back.size() + front.size())) {
			throw out_of_range("");
		}
		if (pos < front.size()) {
			return front[front.size() - pos - 1];
		}
		else {
			return back[pos - front.size()];
		}
	}

	const T& Front() const {
		if (!front.empty()) {
			return front[front.size() - 1];
		}
		else {
			return back[0];
		}
	}


	T& Front() {
		if (!front.empty()) {
			return front[front.size() - 1];
		}
		else {
			return back[0];
		}
	}


	const T& Back() const {
		if (!back.empty()) {
			return back[back.size() - 1];
		}
		else {
			return front[0];
		}
	}


	T& Back() {
		if (!back.empty()) {
			return back[back.size() - 1];
		}
		else {
			return front[0];
		}
	}


	void PushBack(const T val) {
		back.push_back(val);
		//front.reserve(1); 
		//front.assign(data.rbegin(), data.rend());
	}

	void PushFront(const T& val) {
		front.push_back(val);
		//data.reserve(1);
		//data.assign(front.rbegin(), front.rend());
	}

private:
	vector<T> back;
	vector<T> front;
};

int main() {
	/*Deque<int> deq;
	deq.PushFront(1);
	cout << deq.At(0) << endl;
	cout << deq.Back() << endl;
	cout << deq.Front() << endl;
	deq.PushFront(2);
	cout << deq.At(0) << " " << deq.At(1) << endl;
	cout << deq.Back() << endl;
	cout << deq.Front() << endl;
	deq.PushBack(3);
	cout << deq.At(0) << " " << deq.At(1) << " " << deq.At(2) << endl;
	cout << deq.Back() << endl;
	cout << deq.Front() << endl;
	deq.PushFront(4);
	cout << deq.At(0) << " " << deq.At(1) << " " << deq.At(2) << " " << deq.At(3) << endl;
	cout << deq.Back() << endl;
	cout << deq.Front() << endl;*/
	return 0;
}