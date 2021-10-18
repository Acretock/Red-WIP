#include <list>
#include <iostream>
#include <algorithm>
#include "profile.h"
using namespace std;

int main() {
	uint32_t size;
	uint32_t whoToAdd, addBefore;
	cout << "Number of pairs: ";
	cin >> size;
	list<uint32_t> result;
	for (uint32_t i = 0; i < size; i++) {
		cin >> whoToAdd >> addBefore; {
			LOG_DURATION("iter ", i);
			auto iter = find(result.begin(), result.end(), addBefore);
			if (iter != result.end()) {
				result.insert(iter, whoToAdd);
			}
			else {
				result.push_back(whoToAdd);
			}
		}
	}
	for (auto iter = result.begin(); iter != result.end(); iter++) {
		cout << *iter << ' ';
	}
	return 0;
}