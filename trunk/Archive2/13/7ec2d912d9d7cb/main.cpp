#include <chrono>
#include <iostream>
using namespace std;
int main() {
    auto start = chrono::high_resolution_clock::now();
    long long total = 0;
    for (int i = 0; i < 2147483647; i++)
    {
        total += i;
    }
    cout << total << endl;
    auto finish = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::nanoseconds>(finish - start).count() << endl;
}