#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
using namespace std;

bool finished=false;
atomic <int> counter=0;

void fun(){
    while(!finished){
        auto copy=++counter;
        cout<<4<<":"<<counter<<":"<<copy<<endl;
     }
    }
void fun2(){
    while(!finished){
        auto copy=++counter;
        cout<<1<<":"<<counter<<":"<<copy<<endl;
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