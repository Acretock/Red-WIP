#include <map>
#include <set>
#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <deque>

using namespace std;

/*class client
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
};*/

/*bool operator<(client left, client right) { // для find
    return left.id < right.id;
}
bool operator<(uint32_t left, client right) { // для find
    return left < right.id;
}
bool operator<(client left, uint32_t right) { // для find
    return left.id < right;
}
*/
class Booking {
public:

    void book(int64_t time, string hotel_name, uint32_t client_id, int room_count) {
        if (hotels.empty()) { // first entry
            add_new_data(time, hotel_name, client_id, room_count);
            uniq_id.insert({ client_id });
            hotels.insert({ hotel_name });
            entries_hotels.insert({ client_id, {hotel_name} });
            client_res.insert({ hotel_name, 1 });
            rooms_res.insert({ hotel_name,room_count });
            total_for_client.insert({ client_id , 1 });
        } else {
            auto last = last_time.back();
            auto t = abs(time - last);
            auto res = t / 86400;
            if (res == 0) { // no new day
                step(time, hotel_name, client_id, room_count);
            }
            else { // new day
                remove_old_data();

                step(time, hotel_name, client_id, room_count);
            }

        }
    }

    int clients(string hotel_name) {
        if (client_res.count(hotel_name) == 0) {
            return 0;
        }
        else {
            return client_res.at(hotel_name);
        }
    }

    uint64_t rooms(string hotel_name) {
        if (rooms_res.count(hotel_name) == 0) {
            return 0;
        }
        else {
            return rooms_res.at(hotel_name);
        }
    }

private:
    // data
    deque<int64_t> last_time;
    deque<string> last_hotel;
    deque<uint32_t> last_id;
    deque<int> last_room;
    set<string> hotels;

    //clients
    set<uint32_t> uniq_id;
    map<uint32_t, int> total_for_client;
    map<uint32_t, set<string>> entries_hotels;

    //results
    map<string, int> client_res;
    map<string, uint64_t> rooms_res;

    bool new_hotel(string hotel) {
        return (hotels.count(hotel) == 0);
    }
    bool new_client(uint32_t id) {
        return (uniq_id.count(id) == 0);
    }
    void add_new_data(int64_t time, string hotel_name, uint32_t client_id, int room_count) {
        last_time.push_back(time);
        last_hotel.push_back(hotel_name);
        last_id.push_back(client_id);
        last_room.push_back(room_count);
    }

    void remove_old_data() {
        if (total_for_client.find(last_id.front())->second == 1) {
            auto hotel = *entries_hotels.find(last_id.front())->second.begin();
            entries_hotels.erase(last_id.front());
            total_for_client.erase(last_id.front());
            uniq_id.erase(last_id.front());
            if (client_res.find(hotel)->second == 1) {
                hotels.erase(hotel);
                client_res.erase(hotel);
                rooms_res.erase(hotel);
            } else {
                client_res.find(hotel)->second--;
                rooms_res.find(hotel)->second-= last_room.front();
            }
        } else {
            for (auto hotel : entries_hotels.find(last_id.front())->second) {
                total_for_client.find(last_id.front())->second--;
                if (client_res.find(hotel)->second == 1) {
                    hotels.erase(hotel);
                    client_res.erase(hotel);
                    rooms_res.erase(hotel);
                }
                else {
                    client_res.find(hotel)->second--;
                    rooms_res.find(hotel)->second -= last_room.front();
                }
            }
        }

        last_time.pop_front();
        last_hotel.pop_front();
        last_id.pop_front();
        last_room.pop_front();
    }

    void step(int64_t time, string hotel_name, uint32_t client_id, int room_count) {
        add_new_data(time, hotel_name, client_id, room_count);
        if (new_hotel(hotel_name)) { // new hotel
            hotels.insert({ hotel_name });
            client_res.insert({ hotel_name, 1 });
            rooms_res.insert({ hotel_name,room_count });
            if (new_client(client_id)) {
                uniq_id.insert({ client_id });
                total_for_client.insert({ client_id, 1 });
                entries_hotels.insert({ client_id, {hotel_name} });
            } else {
                total_for_client.find(client_id)->second++;
                entries_hotels.find(client_id)->second.insert({ hotel_name });
            }
        } else if (new_client(client_id)) { // old hotel
            uniq_id.insert({ client_id });
            total_for_client.insert({ client_id, 1 });
            entries_hotels.insert({ client_id, {hotel_name} });
            client_res.find(hotel_name)->second++;
            rooms_res.find(hotel_name)->second += room_count;
        } else { // old hotel, old client
            total_for_client.find(client_id)->second++;
            rooms_res.find(hotel_name)->second += room_count;
        }

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
        } else if (query_type == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.clients(hotel_name) << "\n";
        } else if ("ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.rooms(hotel_name) << "\n";
        }
    }

    return 0;
}
