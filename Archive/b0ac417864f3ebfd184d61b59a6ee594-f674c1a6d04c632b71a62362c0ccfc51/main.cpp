#include <thread>
#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

void sortfunc(int i) {
    usleep(i * 1000);
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
    s({9, 8, 7, 3, 4, 2, 1, 5});
}