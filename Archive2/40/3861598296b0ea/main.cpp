#include <thread>
#include <iostream>
#include <chrono>

using namespace std;

bool finish = false;
int counter = 0;

void fun() {
    while(!finish) {
        auto copy = ++counter;
        cout << "fun:" << counter << " : " << copy << endl;
    }
}

void fun2() {
    while(!finish) {
        auto copy = ++counter;
        cout << "fun:" << counter << " : " << copy << endl;
    }    
}

int main() {
    using namespace std::chrono;
    auto t1 = thread(fun);
    auto t2 = thread(fun2);
    //this_thread::sleep_for(chrono::milliseconds(100));
    this_thread::sleep_for(milliseconds(100));
    finish = true;
    t1.join();
    t2.join();
    return 0;
}