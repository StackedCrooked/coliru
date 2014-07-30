#include <chrono>    // std::chrono::milliseconds
#include <iostream>  // std::cout
#include <mutex>     // std::mutex  std::lock_guard
#include <thread>    // std::thread


void print_block(int n, char c)
{
    while( n-- )
	{
		std::cout << c;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	std::cout << '\n';
}

std::mutex mtx;           // mutex for critical section

void print_critial_block(int n, char c)
{
	  // locking mutex and entering critical section
	mtx.lock();
	while( n-- )
	{
		std::cout << c;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	std::cout << '\n';
	mtx.unlock();
	  // unlocking mutex and leaving critical section
}

void print_locked_block(int n, char c)
{
	std::lock_guard<std::mutex> locker(mtx);
	  // mutex is locked until lock_guard is destroyed
	while( n-- )
	{
		std::cout << c;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	std::cout << '\n';
}

int main()
{
    std::cout << "========= asynchronized runs ============\n";
  {
	std::thread th1(print_block, 40, '*');
	std::thread th2(print_block, 40, '$');

	th1.join();
	th2.join();
  }

	std::cout << "========= synchronized runs =============\n";
  {
	std::thread th1(print_critial_block, 40, '*');
	std::thread th2(print_locked_block,  40, '$');

	th1.join();
	th2.join();
  }

	return 0;
}
