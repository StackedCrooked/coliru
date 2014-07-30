#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable


std::mutex mtx;
std::condition_variable cv;
bool started = false;


void print_id(int id)
{
      // lock mutex
	std::unique_lock<std::mutex> lck(mtx);
	std::cout << id << " ready\n";

	while( ! started )
	{
		std::cout << id << " waiting\n";
		  // unlock mutex and wait for notification
		cv.wait(lck);
		  // after getting notification try to lock mutex
	}

//	auto condition = [&]{ if(!started) std::cout<<id<<" waiting\n"; return started; };
//	cv.wait(lck, condition);  // equivalent to:  while (!condition()) wait(lck);

	std::cout << id << " finished\n";
	  // unlock mutex on exit (destroy unique_lock)
}

void trigger_start()
{
	  // lock mutex
	std::unique_lock<std::mutex> lck(mtx);
	std::cout << "10 threads ready to race...  Go!\n";
	started = true;
	  // send notification to all subscribers and...
	cv.notify_all();  // note that sending notification doesn't unlock mutex
	  // ...exit function unlocking mutex
}

int main()
{
	std::thread threads[10];
	  // spawn 10 threads:
	for( int i = 0 ; i < 10 ; ++i )
		threads[i] = std::thread(print_id, i);

	trigger_start();  // send notification to all threads

	for( auto& th : threads )
		th.join();

	return 0;
}
