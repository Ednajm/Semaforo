#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    while (true) {

        cout << "RED: ON" << endl;
        cout << "YELLOW: OFF" << endl;
        cout << "GREEN: OFF" << endl << endl;
        this_thread::sleep_for(chrono::seconds(5));

        cout << "RED: OFF" << endl;
        cout << "YELLOW: ON" << endl;
        cout << "GREEN: OFF" << endl << endl;
        this_thread::sleep_for(chrono::seconds(2));

        cout << "RED: OFF" << endl;
        cout << "YELLOW: OFF" << endl;
        cout << "GREEN: ON" << endl << endl;
        this_thread::sleep_for(chrono::seconds(5));
    }

    return 0;
} 
