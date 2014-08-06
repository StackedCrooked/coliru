#include<vector>    
#include<deque>
#include <iostream>
#include <chrono>
using namespace std;

int main(int argc, char** argv)
{ 
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;
    
    vector<unsigned short> v = vector<unsigned short>(1024*1024);
    vector<unsigned short> v2;
    deque<vector<unsigned short> > d;

    auto start = high_resolution_clock::now();
    d.push_back(v);
    auto stop = high_resolution_clock::now();
    milliseconds dur = std::chrono::duration_cast<milliseconds>(stop-start);
    std::cout << "first test took " << dur.count() << "ms\n";

    // takes less than 5msec
    start = high_resolution_clock::now();
    d.push_back(v2);
    d.back() = v;
    stop = high_resolution_clock::now();
    dur = std::chrono::duration_cast<milliseconds>(stop-start);
    std::cout << "second test took " << dur.count() << "ms\n";

    return 0;
}