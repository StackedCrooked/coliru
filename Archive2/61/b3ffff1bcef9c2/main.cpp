#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
using namespace std;

bool stop1;
bool stop2;
int a=0;
mutex l1;
mutex l2;

void fun1() {
    while(!stop1) {
        l1.lock();
    	cout << 1 <<" : " << a << endl;
        a++;
        l2.unlock();
	}
}
 
void fun2() {   
	while(!stop2) {
        l2.lock();
    	cout << 4 <<" : " << a << endl;
        a++;
        l1.unlock();
	}
}
 
int main() {
    stop1=false;
    stop2=false;
	auto thread1 = thread(fun1);
	auto thread2 = thread(fun2);
	this_thread::sleep_for(chrono::milliseconds(4));
    stop1 = true;
    stop2 = true;
    this_thread::sleep_for(chrono::milliseconds(1));
	return 0;
}