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
    bool alive_;
    thread thread_;
};

int main() {
    solution_using_thread solution;
    this_thread::sleep_for(chrono::milliseconds(5));
}
