#include <thread>
#include <iostream>
#include <pthread.h>
 
using namespace std;

void foo()
{
    string s = "thread1";
    pthread_setname_np(pthread_self(), s.c_str()); // set the name (pthread_self() returns the pthread_t of the current thread)
    cout << this_thread::get_id() << endl;
}

int main() 
{
    thread t1(foo);
 
    string s = "thread1";
 
    t1.join();
    return 0;
}
