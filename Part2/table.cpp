#include "test_runner.h"
#include <vector>
#include <utility>
#include <iostream>
using namespace std;

template<typename T>
class Table
{
public:
	Table(size_t collums, size_t rows) : collums(collums), rows(rows) {
		Resize(collums, rows);
	}
	pair<size_t, size_t> Size() const {
		if (rows != 0u && collums != 0u) {
			return make_pair(collums, rows);
		}
		else {
			return make_pair(0u, 0u);
		}

	}

	vector<T>& operator[](size_t pos) {
		return value[pos];
	}

	const vector<T>& operator[](size_t pos) const {
		return value[pos];
	}

	void Resize(size_t in_collums, size_t in_rows) {
		value.resize(in_collums);
		for (auto& item : value) {
			item.resize(in_rows);
		}
		collums = in_collums;
		rows = in_rows;
	}


private:
	size_t collums;
	size_t rows;
	vector<vector<T>> value;
};



void TestTable() {
	Table<int> t(1, 2);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
	t.Resize(1, 2);
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 2u);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestTable);
	return 0;
}
