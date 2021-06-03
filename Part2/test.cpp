#include "test_runner.h"

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

                it.second = (1.0 / page_counter[page_count]);

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
        if (GetUserCount() == 1) {
            return 1;
        }
        else if (score.size() == 0) {
            return 0;
        }
        else {
            return score.find(person.find(user_id)->second)->second;
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
    void updatePages() {}
};

using namespace std;

class ReadingManagerOld {
public:
    ReadingManagerOld()
        : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        sorted_users_(),
        user_positions_(MAX_USER_COUNT_ + 1, -1) {}

    void Read(int user_id, int page_count) {
        if (user_page_counts_[user_id] == 0) {
            AddUser(user_id);
        }
        user_page_counts_[user_id] = page_count;
        int& position = user_positions_[user_id];
        while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
            SwapUsers(position, position - 1);
        }
    }

    double addCheer(int user_id) const {
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
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;

    vector<int> user_page_counts_;
    vector<int> sorted_users_;   // РѕС‚СЃРѕСЂС‚РёСЂРѕРІР°РЅС‹ РїРѕ СѓР±С‹РІР°РЅРёСЋ РєРѕР»РёС‡РµСЃС‚РІР° СЃС‚СЂР°РЅРёС†
    vector<int> user_positions_; // РїРѕР·РёС†РёРё РІ РІРµРєС‚РѕСЂРµ sorted_users_

    int GetUserCount() const {
        return sorted_users_.size();
    }
    void AddUser(int user_id) {
        sorted_users_.push_back(user_id);
        user_positions_[user_id] = sorted_users_.size() - 1;
    }
    void SwapUsers(int lhs_position, int rhs_position) {
        const int lhs_id = sorted_users_[lhs_position];
        const int rhs_id = sorted_users_[rhs_position];
        swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
        swap(user_positions_[lhs_id], user_positions_[rhs_id]);
    }
};

