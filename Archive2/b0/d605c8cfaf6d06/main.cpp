#include <iostream>
#include <thread>
    
static const int NUM_THREADS = 10;

// Thread function. When a thread is launched, this is the code that gets
// executed.
void ThreadFunction(int threadID) {
    
	std::cout << "Hello from thread #" << threadID << std::endl;
}

int main() {
	
	std::thread thread[NUM_THREADS];

	// Launch threads.
	for (int i = 0; i < NUM_THREADS; ++i) {
		thread[i] = std::thread(ThreadFunction, i);
	}
	
	std::cout << NUM_THREADS << " threads launched." << std::endl;

	// Join threads to the main thread of execution.
	for (int i = 0; i < NUM_THREADS; ++i) {
		thread[i].join();
	}
	
	return 0;
}

// Typical program output is shown below ...
//
// Hello from thread #Hello from thread #Hello from thread #0
// 3
// Hello from thread #Hello from thread #24
//
// 1
// Hello from thread #5
// Hello from thread #6
// Hello from thread #7
// Hello from thread #8
// 10Hello from thread #9
//  threads launched.

// Copyright (C) 2013, Andrew J. T. Sheppard, all rights reserved.
