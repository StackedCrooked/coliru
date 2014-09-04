#include <iostream>
#include <thread>
#include <sstream>
using namespace std;
 
thread_local int i;

stringstream o1, o2, o3;
 
int main() {
    thread t1([]{
		o1 << "&i of " << this_thread::get_id() << " = " << &i << endl;
	});
	thread t2([]{
		o2 << "&i of " << this_thread::get_id() << " = " << &i << endl;
	});
	o3 << "&i of " << this_thread::get_id() << " = " << &i << endl;
	t1.join();
	t2.join();
	cout << o1.str() << o2.str() << o3.str();
	return 0;
}
