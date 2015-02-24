#include <iostream>
#include <thread>
#include<chrono>
using namespace std;

bool finished=false;

void fun(){
    while(!finished){
     cout<<4<<endl;
     }
    }
void fun2(){
    while(!finshed){
        cout<<1<<endl;
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