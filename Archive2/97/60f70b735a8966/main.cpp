#include <iostream>
#include <iomanip>
#include <mutex>
#include <thread>
#include <string>

using namespace std;

ostream& operator<<(ostream& os, lock_guard<mutex>&& lg)
{
    return os;
}

using lock_with = lock_guard<mutex>;

int main()
{
    mutex m;
    thread t1{[&]{
        cout << lock_with(m) << "Hello thread 1 " << " concateno 1" << endl;    
    }};
    thread t2{[&]{
        cout << lock_with(m) << "Hello thread 2 " << " concateno 2" << endl;    
    }};
    thread t3{[&]{
        cout << lock_with(m) << "Hello thread 3 " << " concateno 3" << endl;    
    }};
    t1.join();t2.join();t3.join();
}