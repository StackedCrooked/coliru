#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
using namespace std;

bool stop = true;
atomic<int> a;

void fun() {
    while(stop) {
		cout << 1 <<" : " << a << endl;
        a++;
	}
}
 
void fun2() {
	while(stop) {
    	cout << 4 <<" : " << a << endl;
        a++;
	}
}
 
int main() {
	auto thread1 = thread(fun);
	auto thread2 = thread(fun2);
	this_thread::sleep_for(chrono::milliseconds(1));
    stop = false;
	return 0;
}