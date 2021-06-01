#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <algorithm>
#include "profile.h"

using namespace std;

class ReadingManager {
public:
    ReadingManager() {
        person.insert({ -1,-1 });
        data.insert({ 0,{-1} });
    }

    void Read(int user_id, int page_count) {
        LOG_DURATION("read");

        if ((person.count(user_id)) == 0) {
            data.insert({ page_count,{user_id} });
            person.insert({ user_id,page_count });
        }
        else {
            if (data.find(person.at(user_id))->second.size() == 1) {
                data.erase(person.at(user_id));
                data[page_count].insert(user_id);
                person[user_id] = page_count;
            }
            else {
                data.find(person.at(user_id))->second.erase(user_id);
                data[page_count].insert(user_id);
                person[user_id] = page_count;
            }
        }
    }

    double Cheer(int user_id) const {
        const int user_count = GetUserCount();
        if (user_count == 1) {
            return 1;
        }
        int position;
        if (data.size() == 1) {
            position = 0;
        }
        else {
            position = GetUserCount() + 1;
            for (auto it = next(data.begin()); it->second.count(user_id) != 0; ++it) {
                position -= it->second.size();
            }
        }
        if (position == user_count) {
            return 0;
        }
        
        auto it = data.upper_bound(person.at(user_id));
        if (it == data.end() && prev(it)->second.size() == 1) {
            return 1;
        }
        return (static_cast<double>(position - user_count) / static_cast<double>(user_count - 1));
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;

    // map<vector<int>,int> data2; // первое страницы, второе индекс людей на ней
    map<int, set<int>> data; // первое страницы, второе индекс людей на ней
    map<int, int> person; // первое страницы, второе индекс людей на ней

    int GetUserCount() const {
        return person.size() - 1;
    }
};


int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}