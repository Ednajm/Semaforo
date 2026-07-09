#include <iostream>
#include <thread>
#include <chrono>
using namespace std;
enum State { RED, GREEN, YELLOW };
int main() {
    State state = RED;
    while (true) {
        switch (state) {
            case RED:
                cout << "RED: ON  YELLOW: OFF  GREEN: OFF" << endl;
                this_thread::sleep_for(chrono::seconds(5));
                state = GREEN;
                break;
            case GREEN:
                cout << "RED: OFF  YELLOW: OFF  GREEN: ON" << endl;
                this_thread::sleep_for(chrono::seconds(5));
                state = YELLOW;
                break;
            case YELLOW:
                cout << "RED: OFF  YELLOW: ON  GREEN: OFF" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                state = RED;
                break;
        }
    }
    return 0;
} 
