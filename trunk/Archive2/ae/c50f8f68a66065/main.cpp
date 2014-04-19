#include <iostream>
#include <thread>
#include <sys/resource.h>
#include <sys/time.h>

using namespace std;

void tf(void)
{
    rlimit rl;
	getrlimit(RLIMIT_AS, &rl);
	cout << "Soft memory limit is " << rl.rlim_cur << endl;
	cout << "Hard memory limit is " << rl.rlim_max << endl;
}


int main() {
	
	rlimit rl;
	tf();
	rl.rlim_cur = 123456789; 
	rl.rlim_max = 234567890;
	setrlimit(RLIMIT_AS, &rl);
	tf();
	thread t(tf);
	t.join();
	return 0;
}