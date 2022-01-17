#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "profile.h"
#include "test_runner.h"
#include <algorithm>

using namespace std;

template <typename String>
using Group = vector<String>;

template <typename String>
using Char = typename String::value_type;

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
	vector<set<Char<String>>> charGroups;
	vector<Group<String>> result;
	for (size_t i = 0; i < strings.size(); i++) {	// for each word
		charGroups.push_back({ strings[i].begin(), strings[i].end() }); // add cuttent char group
        bool ins = false;
		for (size_t j = 0; j < charGroups.size() - 1; j++) {
			if (charGroups.back() == charGroups[j]) { // if exist, then add to res
				result[j].push_back(strings[i]);
                ins = true;
                charGroups.pop_back();
				break;
			}
		}
        if (!ins) {
            result.push_back({ strings[i] });
        }
	}
	return result;
}

template <typename String>
vector<Group<String>> GroupHeavyStrings1(vector<String> strings) {
    // Напишите реализацию функции,
    // использовав не более 1 копирования каждого символа
    map <set<Char<String>>, Group<String>> total;
    for (auto& word : strings) {
        set<Char<String>> _word;
        for (auto& letter : word) {
            _word.insert(move(letter));
        }
        total[_word].push_back(move(word));
    }
    vector<Group<String>> result;
    for (auto& a : total)
        result.push_back(move(a.second));
    return result;
}

void TestGroupingABC() {
    vector<string> strings = { "caab", "abc", "cccc", "bacc", "c" };
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 2);
    sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], vector<string>({ "caab", "abc", "bacc" }));
    ASSERT_EQUAL(groups[1], vector<string>({ "cccc", "c" }));
}

void TestGroupingReal() {
    vector<string> strings = { "law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl" };
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 4);
    sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], vector<string>({ "laptop", "paloalto" }));
    ASSERT_EQUAL(groups[1], vector<string>({ "law", "wall", "awl" }));
    ASSERT_EQUAL(groups[2], vector<string>({ "port" }));
    ASSERT_EQUAL(groups[3], vector<string>({ "top", "pot" }));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestGroupingABC);
    RUN_TEST(tr, TestGroupingReal);
    return 0;
}