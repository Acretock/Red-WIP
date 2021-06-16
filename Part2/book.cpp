#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <algorithm>
#include "profile.h"
#include <cmath>
using namespace std;

class ReadingManager {
public:
    ReadingManager()
        : pages_users_(MAX_PAGE_COUNT_ + 1)
    {}

    void Read(int user_id, int page_count) {
        int prev_page;
        if (users_pages_.count(user_id) == 0) {
            AddUser(user_id, page_count);
        }
        else {
            prev_page = users_pages_[user_id];
            pages_users_[prev_page].erase(user_id);
            AddUser(user_id, page_count);

        }
    }

    double Cheer(int user_id) const {

        if (users_pages_.count(user_id) == 0) {
            return 0;
        }

        const int user_all = GetUserCount();

        if (user_all == 1) {
            return 1;
        }

        int page_base = users_pages_.at(user_id);
        int user_value = 0;

        for (int i = 1; i < page_base; i++) {
            user_value += pages_users_[i].size();
        }
        return (1.0 * user_value) / (user_all - 1);
    }

private:
    static const int MAX_PAGE_COUNT_ = 1000;
    map<int, int> users_pages_;
    vector<set<int>> pages_users_;
    void AddUser(int user_id, int page_count) {
        users_pages_[user_id] = page_count;
        pages_users_[page_count].insert(user_id);
    }
    int GetUserCount() const {
        return users_pages_.size();
    }

};

int main() {
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