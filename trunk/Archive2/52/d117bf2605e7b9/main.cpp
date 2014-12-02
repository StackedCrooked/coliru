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
	std::atomic_thread_fence(std::memory_order_acq_rel);
	r1 = Y.load(std::memory_order_relaxed);
}
static void t2() {
	Y.store(1, std::memory_order_relaxed);
	std::atomic_thread_fence(std::memory_order_acq_rel);
	r2 = X.load(std::memory_order_relaxed);
}

//// non C++-11 way, is exactly the same
//volatile int X2;
//volatile int Y2;
//#include "windows.h"
//static void t3() {
//	X2 = 1;
//	MemoryBarrier();
//	r1 = Y2;
//}
//static void t4() {
//	Y2 = 1;
//	MemoryBarrier();
//	r2 = X2;
//}


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
		reset.wait(lock);
	}
}
void loop2()
{
	while (!should_quit)
	{
		std::unique_lock<std::mutex> lock(feed2_m);

		t2();
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
		std::unique_lock<std::mutex> lock(feed2_m);
		std::unique_lock<std::mutex> lock2(feed1_m);
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
			reset.notify_all();
			return;
		}
		r1 = 0;
		r2 = 0;
		}
		reset.notify_all();
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
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