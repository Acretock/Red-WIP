#include "test_runner.h"
#include <vector>
using namespace std;

template<typename T>
class Table
{
public:
	Table(size_t width, size_t height) : width(width), height(height) {
		value.resize(width);
		for (auto i : value) {
			i.resize(height);
		}
	}
	~Table();
	pair<size_t, size_t> Size() {
		return make_pair( height, width);
	}
private:
	size_t width;
	size_t height;
	vector<vector<T>> value;
};



void TestTable() {
	Table<int> t(1, 1);
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestTable);
	return 0;
