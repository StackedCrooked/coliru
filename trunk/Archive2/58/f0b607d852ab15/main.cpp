#include <thread>
#include <iostream>
#include <chrono>
#include <atomic>
#include <mutex>
#include <vector>

using namespace std;

bool finish = false;
atomic<int> counter;
mutex m;
vector<float> vec(200000, 2.1f);
float sum = 0;

void fun() {
    using namespace chrono;
    microseconds t(0);
    while(!finish) {
        auto t1 = high_resolution_clock::now();
        //m.lock();
        sum += vec.pop_back();
        auto copy = ++counter;
        cout << "fun:" << counter << " : " << copy << endl << "T1:" << t.count() << endl;
        for (auto & element : data) {
            count += element;
        }
        //m.unlock();
        auto t2 = high_resolution_clock::now();
        t = duration_cast<microseconds>(t2-t1);
    }
    
}

void fun2() {
    using namespace chrono;
    microseconds t(0);
    while(!finish) {
        auto t1 = high_resolution_clock::now();
        m.lock();
        auto copy = ++counter;
        sum += vec.pop_back();
        cout << "fun2:" << counter << " : " << copy << endl << "T1:" << t.count() << endl;
        m.unlock();
        auto t2 = high_resolution_clock::now();
        t = duration_cast<microseconds>(t2-t1);
    }    
}

int main() {
    using namespace std::chrono;
    int i = 1;
    while (i <= 200000) {
        vec.push_back(2.0);
        i++;
    }
    auto t1 = thread(fun);
    auto t2 = thread(fun2);
    //this_thread::sleep_for(chrono::milliseconds(100));
    this_thread::sleep_for(milliseconds(100));
    finish = true;
    t1.join();
    t2.join();
    cout << sum << endl;
    return 0;
}