#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <set>
#include "profile.h"
using namespace std;

class Learner {
private:
    set<string> helper;
    vector<string> dict;

public:
    int Learn(const vector<string>& words) {
        LOG_DURATION("Learn"); {
            int newWords = 0;
            for (const auto& word : words) {
                if (helper.count(word) == 0) {
                    ++newWords;
                    helper.insert(word);
                    dict.push_back(word);
                }
            }
            return newWords;
        }
    }

    vector<string> KnownWords() {
        LOG_DURATION("KnownWords"); {
            sort(dict.begin(), dict.end());
            //dict.erase(unique(dict.begin(), dict.end()), dict.end());
            return dict;
        }
    }
};

int main() {
    Learner learner;
    string line;
    while (getline(cin, line)) {
        if (line == "q")
            break;
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        cout << learner.Learn(words) << "\n";
    }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords()) {
        cout << word << "\n";
    }
}