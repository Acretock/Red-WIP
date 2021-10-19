#include <iostream>
#include <string>
#include <string_view>
#include <map>
#include <list>
#include "test_runner.h"

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target) {
        data.push_front(source.data());
        data.push_back(target.data());
        forward[data.front()] = data.back();
        backward[data.back()] = data.front();
    }

    string_view TranslateForward(string_view source) const {
        auto search = forward.lower_bound(source);
        if ( (*search).first != source) {
            return string_view{};
        }
        else {
            return (*search).second;
        }
    }

    string_view TranslateBackward(string_view target) const {
        auto search = backward.lower_bound(target);
        if ((*search).first != target) {
            return string_view{};
        }
        else {
            return (*search).second;
        }
    }

private:
    map<string_view, string_view> forward;
    map<string_view, string_view> backward;
    list<string> data;
};

void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "table");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}