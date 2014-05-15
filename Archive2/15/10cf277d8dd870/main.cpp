#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
using namespace std;

atomic<int> a{1};
int main()
{
    thread t1([]{ cout << (++a) << endl; });
    thread t2([]{ cout << (++a) << endl; });
    
    t1.join();
    t2.join();
    cout << a << endl;
}
