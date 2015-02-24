#include <iostream>
#include <thread>
#include<chrono>
using namespace std;

void fun(){
    while(true){
     cout<<4<<endl;
     }
    }
void fun2(){
    while(true){
        cout<<1<<endl;
        }
    }
    
    int main(){
        auto t1=thread(fun);
        auto t2=thread(fun2);
        this_thread::sleep_for(chrono::milliseconds(100));
        return 0;
        }