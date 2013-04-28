#include <thread>
#include <iostream>
#include <pthread.h>
 
using namespace std;

void foo()
{
    char name[16]; // thread names are limited to 16 characters anyway (including the null terminator).
    pthread_getname_np(pthread_self(), name, sizeof(name)); // get the name (pthread_self() returns the pthread_t of the current thread)
    cout << name << endl;
}

int main() 
{
    thread t1(foo);
 
    string s = "thread1";
 
    pthread_setname_np( t1.native_handle(), s.c_str());
 
    t1.join();
    return 0;
}
