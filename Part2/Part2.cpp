#include <map>
#include <set>
#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <deque>

using namespace std;

class Booking
{
public:
    void book(int64_t time, string hotel_name, uint32_t client_id, uint16_t room_count) {
        if (last_booked.count(hotel_name) == 0) {
            last_booked.insert({ hotel_name,time });

        }
        else {

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

    int rooms(string hotel_name) {
        if (res_rooms.count(hotel_name) == 0) {
            return 0;
        }
        else {
            return res_rooms.at(hotel_name);
        }
    }

private:
    map<string, int64_t> last_booked;
    map<string, deque<uint32_t>> clients;
    map<string, deque<uint16_t>> clients;
    map<string, int> res_clients;
    map<string, int> res_rooms;
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Booking manager;
    cout << numeric_limits<uint8_t>::max() / pow(10, 3);
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
