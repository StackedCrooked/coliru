#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

bool finished=false;
int counter;
mutex m;

void fun(){
    using namespace chrono;
    microseconds t(0);
    while(!finished){
        auto t1=high_resolution_clock::now();
     //   m.lock();
        auto copy=++counter;
        cout<<4<<":"<<counter<<":"<<copy<<"t="<<t.count()<<endl;
     //   m.unlock();
        auto t2=high_resolution_clock::now();
        t=duration_cast<microseconds>(t2-t1);
     }
    }
    
void fun2(){
     using namespace chrono;
      microseconds t(0);
    while(!finished){
        auto t1=high_resolution_clock::now();
   //      m.lock();
        auto copy=++counter;
        cout<<1<<":"<<counter<<":"<<copy<<"t="<<t.count()<<endl;
    //     m.unlock();
          auto t2=high_resolution_clock::now();
        t=duration_cast<microseconds>(t2-t1);
        }
    }
    
    int main(){
        using namespace std::chrono;
        auto t1=thread(fun);
        auto t2=thread(fun2);
        this_thread::sleep_for(milliseconds(100));
        finished=true;
        t1.join();
        t2.join();
        return 0;
        }