#include <map>
#include <set>
#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <deque>

using namespace std;

class client
{
public:
    client(string hotel_name, uint32_t client_id) : id(client_id) {
        add_hotel(hotel_name);
    }

    bool has_hotel(string hotel_name) {
        return (hotels.count(hotel_name) != 0);
    }

    bool is_last_entry(string hotel_name) {
        return (entries.find(hotel_name)->second == 1);
    }

    void add_entry(string hotel_name) {
        entries.find(hotel_name)->second++;
    }

    void sub_enrty(string hotel_name) {
        entries.find(hotel_name)->second--;
    }

    void add_hotel(string hotel_name) {
        if (hotels.count(hotel_name) == 0) {
            hotels.insert(hotel_name);
            entries.insert({ hotel_name, 1 });
        }
        else { add_entry(hotel_name); }
    }

    int entrie(string hotel_name) { return entries.at(hotel_name); }
    uint32_t id;
    set<string> hotels;
    map<string, int> entries;
};

bool operator<(client left, client right) { // для find
    return left.id < right.id;
}
bool operator<(uint32_t left, client right) { // для find
    return left < right.id;
}
bool operator<(client left, uint32_t right) { // для find
    return left.id < right;
}

class Booking
{
public:
    void book(int64_t time, string hotel_name, uint32_t client_id, uint64_t room_count) {
        if (last_time.empty()) {
            last_time.push_back(make_pair(time, hotel_name));
            unique_clients.emplace(hotel_name, client_id);
            Rooms.insert({ hotel_name ,{room_count} });
            res_clients.insert({ hotel_name, 1 });
            res_rooms.insert({ hotel_name , room_count });
        }
        else {

            if (not_new_day(time)) { // time OK
                if (new_client(client_id)) {
                    unique_clients.emplace(hotel_name, client_id);
                }
                else {
                    unique_clients.find(client_id)->
                }

            }
            else { // day has passed

            }

        }
    }

    int clients(string hotel_name) {
        if (res_clients.count(hotel_name) == 0) {
            return 0;
        }
        else {
            return res_clients.at(hotel_name);
        }
    }

    uint64_t rooms(string hotel_name) {
        if (res_rooms.count(hotel_name) == 0) {
            return 0;
        }
        else {
            return res_rooms.at(hotel_name);
        }
    }

private:
    deque<pair<int64_t, string>> last_time; // обязательно
    set<client, less<> > unique_clients;             // обязательно
    map<string, deque<client>> hotels;                     // вроде надо
    map<string, int> res_clients;           // обязательно
    map<string, deque<uint64_t>> Rooms;     // вроде надо
    map<string, uint64_t> res_rooms;             // обязательно

    void add_one(int64_t time, string hotel_name, uint32_t client_id, uint64_t room_count) {}
    void remove_one() {}
    bool new_hotel(string hotel_name) {
        return hotels.count(hotel_name) == 0;
    }
    bool new_client(uint32_t client_id) {
        return (unique_clients.count(client_id) == 0);
    }
    bool not_new_day(int64_t time) {
        return ((abs(time - last_time.front().first) / 86400) == 0);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Booking manager;
    //cout << numeric_limits<uint8_t>::max() / pow(10, 3);
    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t time;
            string hotel_name; 
            uint32_t client_id;
            uint16_t room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            manager.book(time, hotel_name, client_id, room_count);
        } else if (query_type == "CLIENTS ") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.clients(hotel_name) << "\n";
        } else if ("ROOMS ") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.rooms(hotel_name) << "\n";
        }
    }

    return 0;
}
