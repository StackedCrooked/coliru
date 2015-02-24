#include <thread>
#include <iostream>
#include <chrono>
#include <atomic>
#include <mutex>

using namespace std;

bool finish = false;
atomic<int> counter;
mutex m;

void fun() {
    using namespace chrono;
    microseconds t(0);
    while(!finish) {
        auto t1 = high_resolution_clock::now();
        m.lock();
        auto copy = ++counter;
        cout << "fun:" << counter << " : " << copy << endl << "T1:" << t.count() << endl;
        m.unlock();
        auto t2 = high_resolution_clock::now();
        t = duration_cast<microseconds>(t2-t1);
    }
    
}

void fun2() {
    while(!finish) {
        m.lock();
        auto copy = ++counter;
        cout << "fun2:" << counter << " : " << copy << endl;
        m.unlock();
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