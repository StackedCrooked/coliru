#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
//--------------------------------------------------------------------------------------//
class Task
{
    public:
    
	mutex m;
	int ctr{0};

	int operator()()
	{
	    m.lock();

	    cout << this_thread::get_id() << ":" << this << " - " << ctr << endl;

	    ctr++;
	    m.unlock();

	    while(ctr>0)
		this_thread::sleep_for(chrono::seconds{3});

	    unique_lock<mutex>lock(m);
	    cout << this_thread::get_id() << " exited" << endl;
	}
};
//--------------------------------------------------------------------------------------//
int func(Task & t)
{
    while(true)
    {
	this_thread::sleep_for(chrono::seconds(3));;

	t.m.lock();
        t.ctr=0;

	cout << "reset " << &t << endl;

	t.m.unlock();
    }
}
//--------------------------------------------------------------------------------------//
int main()
{
    Task task;
    thread t{func, ref(task)};

    while(true)
    {
	cout << "creating threads" << endl;

	thread t1{ref(task)};
	thread t2{ref(task)};
	thread t3{ref(task)};

	t1.join();
	t2.join();
	t3.join();	
    }
}
//--------------------------------------------------------------------------------------//

