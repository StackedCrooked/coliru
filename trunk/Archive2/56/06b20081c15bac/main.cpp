#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
#include <thread>

using namespace std;

int main()
{
    for(int i = 0; i < 16; ++i ) {
        this_thread::sleep_for(chrono::milliseconds{36});
        for(int count = 0; count < 4; ++count) {
            mt19937_64 urng(chrono::high_resolution_clock::now().time_since_epoch().count());
            uniform_int_distribution<> dist(0, RAND_MAX);
            auto rand = [&](){ return dist(urng); };
            cout << rand() << ' ';
            cout << (time( NULL )) << " \n";
        }
        cout << '\n';
    }
}
