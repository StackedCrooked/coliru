#include <iostream>
#include <chrono>
#include <thread>
 
int main()
{
    using namespace std;
    using namespace std::literals;
    
    cout << "Hello waiter" << endl;
    auto start = chrono::high_resolution_clock::now();
    
    this_thread::sleep_for(2s);
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed = end - start;
    
    cout << "Waited " << elapsed.count() << " ms\n";
}