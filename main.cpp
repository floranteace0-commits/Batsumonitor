/*
SR Code-Based Student Entry Monitoring System for BATSU
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class BATSUMonitor {
private:
    vector<string> authorized_list;

public:
    BATSUMonitor() {
        load_database();
    }

    void load_database() {
        ifstream file("students.txt");
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                if (!line.empty()) {
                    authorized_list.push_back(line);
                }
            }
            file.close();
        } else {
            ofstream newFile("students.txt");
            newFile.close();
        }
    }

    bool is_authorized(const string& code) {
        for (const string& sr : authorized_list) {
            if (sr == code) {
                return true;
            }
        }
        return false;
    }

    void log_to_file(const string& sr_code) {
        ofstream log("entry_log.txt", ios::app);

        time_t now = time(0);
        char* dt = ctime(&now);

        log << "ENTRY: " << sr_code << " | TIME: " << dt;

        log.close();
    }

    void verify_process() {
        string user_input;

        cout << "\nEnter SR Code: ";
        cin >> user_input;

        if (is_authorized(user_input)) {
            cout << "ACCESS GRANTED\n";
            log_to_file(user_input);
        } else {
            cout << "ACCESS DENIED\n";
        }
    }
};

int main() {
    BATSUMonitor system;

    cout << "=== BATSU SR-Code Entry System ===\n";

    while (true) {
        system.verify_process();
    }

    return 0;
}