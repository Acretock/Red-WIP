#include <map>
#include <string>
#include <algorithm>
#include "test_runner.h"
#include "profile.h"
#include "student.h"
using namespace std;

bool Compare(const Student& first, const Student& second) {
    LOG_DURATION("Compare");
    return first.Less(second);
    //return first.rating > second.rating;
}

void TestComparison() {
    //LOG_DURATION("Compatison");
    Student newbie{
      "Ivan", "Ivanov", {
        {"c++", 1.0},
        {"algorithms", 3.0}
      },
      2.0
    };

    Student cpp_expert{
      "Petr", "Petrov", {
        {"c++", 9.5},
        {"algorithms", 6.0}
      },
      7.75
    };

    Student guru{
      "Sidor", "Sidorov", {
        {"c++", 10.0},
        {"algorithms", 10.0}
      },
      10.0
    }; {
        LOG_DURATION("Compatison 1");
        ASSERT(Compare(guru, newbie));
    }
    {
        LOG_DURATION("Compatison 2");
        ASSERT(Compare(guru, cpp_expert));
    }
    {
        LOG_DURATION("Compatison 3");
        ASSERT(!Compare(newbie, cpp_expert));
    }
}

void TestSorting() {
    LOG_DURATION("Sorting");
    vector<Student> students{
      {"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
      {"Semen", "Semenov", {{"maths", 4.}}, 4.},
      {"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
      {"Petr", "Petrov", {{"maths", 3.}}, 3.},
      {"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}
    };
    sort(students.begin(), students.end(), Compare);
    ASSERT(is_sorted(students.begin(), students.end(),
        [](Student first, Student second) {
            return first.Less(second);
        })
    );
}

int main() {
    LOG_DURATION("Main");
    TestRunner tr;
    RUN_TEST(tr, TestComparison);
    RUN_TEST(tr, TestSorting);
    return 0;
}



