#include <iostream>
#include <thread>

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
        ato t2=thread(fun2);
        return 0;
        }