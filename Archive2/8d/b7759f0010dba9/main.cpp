#include <atomic>
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

struct solution_using_thread {
    solution_using_thread()
     : alive_(true), thread_() {
        thread_ = thread([this]() {
            while(alive_);
        });
    }
    ~solution_using_thread() {
        alive_ = false;
        thread_.join();
    }
private:
    std::atomic<bool> alive_;
    thread thread_;
};

int main() {
    cout << 0 << endl;
    try {
        cout << -1 << endl;
        solution_using_thread solution;
        cout << -2 << endl;
        throw 1;
    } catch (int i ) {
        cout << i << endl;
    }
    cout << 2 << endl;
}
