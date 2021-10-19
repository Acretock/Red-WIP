#include <iostream>
#include <string>
#include <string_view>
#include <map>
#include <deque>
#include "test_runner.h"

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target) {
        data.push_back({ source.data(),target.data() });
        forward[data.back().first] = data.back().second;
        backward[data.back().second] = data.back().first;
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
    deque<pair<string, string> > data;
};

void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}