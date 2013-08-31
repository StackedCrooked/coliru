#include <thread>
#include <iostream>
#include <pthread.h>
 
using namespace std;

void foo(){

  cout << this_thread::get_id() << endl;
}

int main() {

  thread t1(foo);
 
 string s = "thread1";
 
 pthread_setname_np( t1.native_handle(), s.c_str());
 
  t1.join();
  return 0;
}
