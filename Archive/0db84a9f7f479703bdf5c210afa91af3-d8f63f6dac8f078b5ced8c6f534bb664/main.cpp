#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace this_thread;
using namespace chrono;

void sortfunc(int i) {
    sleep_for(milliseconds{i * 1000});
    cout << i;
}

void s(vector<int> s) {
    vector<thread> ts;
    for(int i : s)
       ts.emplace_back(&sortfunc, i);
    for(thread &t : ts)
       t.join();
}

int main() {
    s({5, 8, 3, 5, 9, 2, 3});
}