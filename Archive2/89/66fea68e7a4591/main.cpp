#include <chrono>    // std::chrono::seconds
#include <iostream>
#include <mutex>     // std::mutex
#include <stdlib.h>  // rand()
#include <thread>    // std::thread  std::this_thread::sleep_for
#include <vector>


void runCounter( const unsigned id, unsigned counterValue );
void runMutexCounter( const unsigned id, unsigned counterValue );

typedef void (*Fun)(const unsigned, unsigned);

void startThreads(Fun runFunc, const unsigned numThreads)
{
    const unsigned counterValue = 5;
	std::vector<std::thread> threads;

	std::cout << "--------------------\nStarting threads\n--------------------\n";
	for( unsigned i = 0 ; i < numThreads ; ++i )
		threads.push_back(
				std::thread(runFunc, 1000 + rand() % 9000, counterValue));

	for( auto& th : threads )
		th.join();
}

int main()
{
	const unsigned numThreads = 3;

	startThreads(runCounter, numThreads);
	startThreads(runMutexCounter, numThreads);

	return 0;
}


void runCounter( const unsigned id, unsigned counterValue )
{
	std::cout << id << ": countdown:" << std::endl;
	for(  ; counterValue > 0 ; --counterValue )
	{
		std::cout << id << ": " <<  counterValue << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << id << ": Lift off!" << std::endl;
}

std::mutex mtx;  // mutex for critical section

void runMutexCounter( const unsigned id, unsigned counterValue )
{
	mtx.lock(); // entering critical section
	std::cout << id << ": countdown:" << std::endl;
	mtx.unlock(); // leaving critical section

	for(  ; counterValue > 0 ; --counterValue )
	{
		mtx.lock();
		std::cout << id << ": " <<  counterValue << '\n';
		mtx.unlock();

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	mtx.lock();
	std::cout << id << ": Lift off!" << std::endl;
	mtx.unlock();
}
