#include <thread>
#include <iostream>
#include <pthread.h>
 
using namespace std;

void foo()
{
    string s = "thread1";
    size_t len = 0;
    char name[16];
    
     pthread_setname_np(pthread_self(), s.c_str()); // set the name (pthread_self() returns the pthread_t of the current thread)
     
     pthread_getname_np(pthread_self(),name, len);   
     cout << static_cast<const void*>(name) << endl;
     cout << this_thread::get_id() << endl;
}

int main() 
{
    thread t1(foo);
 
    t1.join();
    return 0;
}
