//
// file name: threadpool.hpp
//
// This is a general-purpose thread pool.
// High performance.
//
// Dependencies:
//               C++11, Boost.Lockfree.
// Documentation:
//                See: java.util.concurrent.ThreadPoolExecutor
//



#ifndef THREAD_POOL_HPP 
#define THREAD_POOL_HPP 

#include <iostream>
int pp=0;


#include <cstddef>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <chrono>
#include <chrono>
#include <boost/lockfree/queue.hpp>


namespace ThreadPool {
typedef void (*TaskFunction) (void *);

struct Task {
    TaskFunction taskFunction;
	void *arg;
};

class ThreadPool {
public:
	// allocate n nodes for the freelist. 
	explicit ThreadPool(std::size_t n) : taskQueue_(n) {
		shutdownNow_ = false;
		PoolSize_ = 0;
		taskQueueSize_ = 0;
		std::size_t hardware_concurrency = (std::thread::hardware_concurrency() == 0) ? 1 : std::thread::hardware_concurrency();
		corePoolSize_ = hardware_concurrency;
		maximumPoolSize_ = hardware_concurrency;
		keepAliveTime_ = 5 * 60 * 1000;
	}
	ThreadPool( const ThreadPool& ) = delete; 
	ThreadPool( ThreadPool&& ) = delete; 
	ThreadPool& operator=( const ThreadPool& ) = delete; 
	ThreadPool& operator=( ThreadPool&& ) = delete; 

	virtual ~ThreadPool() { }

	// taskFunction: Task Function.
	//          arg: argument that will be passed to taskFunction. 
	void Execute(TaskFunction taskFunction, void *arg) {
		if (PoolSize_ < maximumPoolSize_ && taskQueueSize_ + 1 > PoolSize_) {
			CreateThread();
			std::cout << "if (PoolSize_ < maximumPoolSize_ && taskQueueSize_ + 1 > PoolSize_) {" << '\n';
		}

		Task newTask;
		newTask.taskFunction = taskFunction;
		newTask.arg = arg;

		while (!taskQueue_.push(newTask))
			;

		++ taskQueueSize_;
		conditionVariable_.notify_one();
		std::cout<<"notify.\n";

		if (LargestPoolSize_ < PoolSize_) 
			LargestPoolSize_ = PoolSize_;
	}

	std::size_t GetCorePoolSize() {
		return corePoolSize_; 
	}

	// TimeUnit: milliseconds 
	std::size_t GetKeepAliveTime() {
		return keepAliveTime_;
	}

	std::size_t GetLargestPoolSize() {
		return LargestPoolSize_;
	}

	std::size_t GetMaximumPoolSize() {
		return maximumPoolSize_; 
	}

	std::size_t GetPoolSize() {
		return PoolSize_;
	}

	std::size_t GetTaskQueueSize() {
		return taskQueueSize_;
	}

	void SetCorePoolSize(std::size_t corePoolSize) { 
		corePoolSize_ = corePoolSize; 
	}

	// TimeUnit: milliseconds 
	void SetKeepAliveTime(std::size_t keepAliveTime) {
		keepAliveTime_ = keepAliveTime;
	}

	void SetMaximumPoolSize(std::size_t maximumPoolSize) {
		maximumPoolSize_ = maximumPoolSize; 
	}

	void ShutdownNow() {
		shutdownNow_ = true;
		conditionVariable_.notify_all();
	}

protected:
	inline void CreateThread() {
//		std::thread t(&ThreadPool::StartRoutine, this);
		++pp;
		std::thread t(&ThreadPool::StartRoutine, this, pp);

		t.detach();

		++ PoolSize_;
	}


//	void StartRoutine() {
	void StartRoutine(std::size_t i) {
		std::cout<<i+1<<"外\n";

		Task t;
		bool terminateTheThread = false;
		bool enabled = false;

		while (!shutdownNow_ && !terminateTheThread) {
			do {
				std::unique_lock<std::mutex> lk(mutex_);
				if (enabled) {
					conditionVariable_.wait_for(lk, std::chrono::milliseconds(keepAliveTime_));
				} else {
					conditionVariable_.wait(lk);
				}
			} while(0);

			std::cout<<i+1<<".    conditionVariable_.wait(lk);→exit.\n";

			while (!shutdownNow_) {
				if (taskQueue_.pop(t)) {
					enabled = false;
					-- taskQueueSize_;
					t.taskFunction(t.arg);
					std::cout<<i+1<<"内\n";
				} else {
					std::cout<<i+1<<".    std::lock_guard<std::mutex> lock(terminateTheThreadMutex_);\n";
					std::lock_guard<std::mutex> lock(terminateTheThreadMutex_);
					if (PoolSize_ > corePoolSize_) {
						if (!enabled) {
							enabled = true;
							std::cout<<i+1<<"退出.if (!enabled) {\n";
						} else {
							-- PoolSize_;
							terminateTheThread = true;
							std::cout<<i+1<<"退出.ok.\n";//先搜[退出.ok.];后搜[退出.if (!enabled)]
						}
					}

					break;
				}
			}
		}
	}

	boost::lockfree::queue<Task> taskQueue_;
	std::mutex terminateTheThreadMutex_;
	std::mutex mutex_;
	std::condition_variable conditionVariable_;
	std::size_t LargestPoolSize_;
	std::atomic<bool> shutdownNow_;
	std::atomic<std::size_t> corePoolSize_;
	std::atomic<std::size_t> maximumPoolSize_;
	std::atomic<std::size_t> PoolSize_;
	std::atomic<std::size_t> keepAliveTime_;
	std::atomic<std::size_t> taskQueueSize_;
};
}

#endif  // THREAD_POOL_HPP 


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Example
// Dependencies:
//               Linux 
//


//#include "threadpool.hpp"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

std::atomic<bool> terminateTheProcess(false);
std::atomic<long> cnt(0);

void TaskFunctionTest (void *arg) {
	cnt += *((long*)arg);
}

void socket_send (void *arg) {
}

void socket_recv (void *arg) {
}

void socket_accept (void *arg) {
}

void disk_write (void *arg) {
}

void disk_read (void *arg) {
}

static void signal_handler(int sig, siginfo_t *si, void *unused) {
	terminateTheProcess = true;
}

void Cleanup() {
	std::cout<<"Cleanup().\n";
}

int main() {
	// signal handling.
	// top(1), pid
	// kill pid
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = signal_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("sigaction");
	if (sigaction(SIGTERM, &sa, NULL) == -1)
		perror("sigaction");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror("sigaction");

	do {
		ThreadPool::ThreadPool tp(12345);
/*
		ThreadPool::ThreadPool tp_error(tp);
		ThreadPool::ThreadPool tp_error2(std::move(tp));

		ThreadPool::ThreadPool tp_error3(1);
		tp_error3 = tp;
		tp_error3 = std::move(tp);
*/

		std::cout << "std::thread::hardware_concurrency() = " << std::thread::hardware_concurrency() << '\n';
		std::cout << "default value:" << '\n';
		std::cout << "    corePoolSize = " << tp.GetCorePoolSize() << ", maximumPoolSize = " << tp.GetMaximumPoolSize() << ", keepAliveTime = " << tp.GetKeepAliveTime() << " ms." << '\n';
//		tp.SetCorePoolSize(4);
//		tp.SetMaximumPoolSize(8);
//		tp.SetKeepAliveTime(2 * 1000);
		std::cout << "new value:" << '\n';
		std::cout << "    corePoolSize = " << tp.GetCorePoolSize() << ", maximumPoolSize = " << tp.GetMaximumPoolSize() << ", keepAliveTime = " << tp.GetKeepAliveTime() << " ms." << '\n';

		auto start = std::chrono::high_resolution_clock::now();

//		const long SIZE = 10000;
		const long SIZE = 1000;
//		const long SIZE = 100;
		long intArray[SIZE];
		for (long i = 0;i < SIZE;++ i) {
			intArray[i] = i;
			tp.Execute(TaskFunctionTest, &intArray[i]);
		}

		// ......

		for (;;) {
			//nfds = epoll_wait(epollfd, events, MAX_EVENTS, 1000);
			if (terminateTheProcess) {
				tp.ShutdownNow();
				Cleanup(); 
				break;
			}

			// ......

			while (tp.GetTaskQueueSize() > 0)
				;

			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> difference = end - start;
			std::cout << "time = " << difference.count() << " s\n";
			std::cout << "cnt = " << cnt << '\n';

			//kill(getpid(), SIGINT);
			kill(getpid(), SIGTERM);
			//kill(getpid(), SIGQUIT);
		}
	} while(0);

	return 0;
}

/*
java，线程池，thread pool
线程池，thread pool，java 
*/


