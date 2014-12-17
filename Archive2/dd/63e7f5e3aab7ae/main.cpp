//http://ideone.com/hFj7Mr

#include <iostream>
#include <fstream>
#include <atomic>
#include <thread>
#include <chrono>
#include <condition_variable>
using namespace std;

atomic<int> X;
atomic<int> Y;
int r1, r2;
static void t1() {
    X.store(1, std::memory_order_relaxed);
	std::atomic_thread_fence(std::memory_order_seq_cst);
	r1 = Y.load(std::memory_order_relaxed);
}
static void t2() {
	Y.store(1, std::memory_order_relaxed);
	std::atomic_thread_fence(std::memory_order_seq_cst);
	r2 = X.load(std::memory_order_relaxed);
}


std::mutex feed1_m;
std::mutex feed2_m;
std::condition_variable reset;
bool should_quit = false;

void loop1()
{
	while (!should_quit)
	{
		std::unique_lock<std::mutex> lock(feed1_m);

		t1();
    	printf("exectuted1\n");
		reset.wait(lock);
	}
}
void loop2()
{
	while (!should_quit)
	{
		std::unique_lock<std::mutex> lock(feed2_m);

		t2();
        printf("exectuted2\n");
		reset.wait(lock);
	}
}
void loop3()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(5));
	reset.notify_all();
	static int tries = 0;
	while (1)
	{
		{
            feed2_m.lock();
            feed1_m.lock();
		if (r1 == 0 && r2 == 0)
		{
			std::cout << "it happened" << std::endl;
		}
		else
		{
			std::cout << "r1: " << r1 << " r2: " << r2 << std::endl;
		}

		if (tries++ > 100)
		{
			should_quit = true;
            feed2_m.unlock();
            feed1_m.unlock();
			reset.notify_all();
			return;
		}
		r1 = 0;
		r2 = 0;
		X=0;
		Y=0;
            feed2_m.unlock();
            feed1_m.unlock();
		}
		reset.notify_all();
    	reset.notify_all();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}


int main()
{
	std::thread t1(loop1), t2(loop2);
	loop3();
	t1.join();
	t2.join();
	return 0;
}