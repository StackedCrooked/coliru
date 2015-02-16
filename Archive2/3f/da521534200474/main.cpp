#include <iostream>
#include <map>
#include <chrono>
#include <cstdio>
using namespace std;

int get(map<string, int> &e, char *s) { return e[s]; }
int set(map<string, int> &e, char *s, int value) { return e[s] = value; }

using Clock = std::chrono::high_resolution_clock;

template <typename Reso = std::chrono::microseconds> Reso getElapsed(Clock::time_point const &since) {
    return chrono::duration_cast<Reso>(Clock::now() - since);
}

int main() {
    map<string, int> Employees;
    std::string buf(10, '\0');

    auto ts = Clock::now();
    for (int i = 0; i < 1000000; i++) {
        buf.resize(std::sprintf(&buf[0], "%08d", i));
        Employees[buf] = i % 1000;
    }
    std::cout << "took " << getElapsed(ts).count() / 1000000.0 << " sec\n";
    cout << Employees["00001234"] << endl;
}
