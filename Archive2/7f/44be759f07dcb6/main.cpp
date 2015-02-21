#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
using namespace std;

bool stop;
bool stop2;
int a;
mutex l;

void fun() {
    while(!stop) {
        l.lock();
		cout << 1 <<" : " << a << endl;
        a++;
        l.unlock();
	}
}
 
void fun2() {
	while(!stop2) {
        l.lock();
    	cout << 4 <<" : " << a << endl;
        a++;
        l.unlock();
	}
}
 
int main() {
    stop = false;
    stop2 = false;
    this_thread::sleep_for(chrono::milliseconds(1));
    
	auto thread1 = thread(fun);
	auto thread2 = thread(fun2);
	this_thread::sleep_for(chrono::milliseconds(100));
    
    stop = true;
    stop2 = true;
    this_thread::sleep_for(chrono::milliseconds(1));
	return 0;
}