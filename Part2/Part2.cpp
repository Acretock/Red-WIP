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
    void Read(int user_id, int page_count) {
        if ((person.count(user_id)) == 0) {
            createPage(page_count);
            person.insert({ user_id,page_count }); 
        }
        else {
            delPage(person[user_id]);
            person[user_id] = page_count;
            createPage(page_count);
        }
        if (score.count(person[user_id]) == 0) {
            score.insert({ page_count,-1.0 });
        }
        else {

        }
        auto count = GetUserCount();
        auto position = 0;
        for (auto& it : score) {
                position++;
            if (position == count) {

                it.second = (1.0 / page_counter[page_count] ) ;

            }
            else if (position != 1) {
                it.second = ((count - position) * 1.0 / (count - 1));
            }
            else { it.second = 0.0; }
        }
    }

    /*
  double Cheer(int user_id) const {
    if (user_page_counts_[user_id] == 0) {
      return 0;
    }
    const int user_count = GetUserCount();
    if (user_count == 1) {
      return 1;
    }
    const int page_count = user_page_counts_[user_id];
    int position = user_positions_[user_id];
    while (position < user_count &&
      user_page_counts_[sorted_users_[position]] == page_count) {
      ++position;
    }
    if (position == user_count) {
        return 0;
    }
    return (user_count - position) * 1.0 / (user_count - 1);
  }*/
    double Cheer(int user_id) const {
        if (GetUserCount() == 1 ) {
            return 1;
        } else if (score.size() == 0) {
            return 0;
        }
        else {
            return score.find(person.find(user_id)->second)->second;
        }
    }
    void createPage(int page_count) {
        if (page_counter.count(page_count) == 0) {
            page_counter.insert({ page_count , 1 });
        }
        else {
            page_counter.find(page_count)->second++;
        }
    }
    void delPage(int page_count) {
        if (page_counter.find(page_count)->second == 1) {
            page_counter.erase(page_counter.find(page_count));
            score.erase(score.find(page_count));
        }
        else {
            page_counter.find(page_count)->second--;
        }
    }
private:
    static const int MAX_USER_COUNT_ = 100'000;

    // map<vector<int>,int> data2; // первое страницы, второе индекс людей на ней
    map<int, double> score;  // страница и счет страницы 
    map<int, int> person; // человек и на какой он странице
    map<int, int> page_counter; // страница и кол-во людей на ней (для добавления)

    int GetUserCount() const {
        return person.size();
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