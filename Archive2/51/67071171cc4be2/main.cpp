//
// file name: threadpool.hpp
//
// This is a general-purpose thread pool.
// High performance.
// Dependencies:
//               C++11, Boost.Lockfree.
//



#ifndef THREAD_POOL_HPP 
#define THREAD_POOL_HPP 

#include <iostream>
#include <cstddef>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
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
		terminateTheProcess_ = false;
		currentThreads_ = 0;
		taskQueueSize_ = 0;
		// Time-sharing.
		long long hardware_concurrency = (std::thread::hardware_concurrency() == 0) ? 1 : std::thread::hardware_concurrency();
	//	int milliseconds = 1000;
	//	int timeslice = 100; // see sched_rr_get_interval(2).
	//	int factor = milliseconds/timeslice;
		corePoolSize_    = hardware_concurrency;
		maximumPoolSize_    = hardware_concurrency;// * 2;
		keepAliveTime_ = 5 * 60;
	}
	ThreadPool( const ThreadPool& ) = delete; 
	ThreadPool( ThreadPool&& ) = delete; 
	ThreadPool& operator=( const ThreadPool& ) = delete; 
	ThreadPool& operator=( ThreadPool&& ) = delete; 

	virtual ~ThreadPool() { }

	// taskFunction: Task Function.
	//          arg: argument that will be passed to taskFunction. 
	void Execute(TaskFunction taskFunction, void *arg) {
		if (corePoolSize_ > currentThreads_) {
			NewThread();
			std::cout << "if (corePoolSize_ > currentThreads_) {" << '\n';
		} else if (currentThreads_ < maximumPoolSize_ && taskQueueSize_ + 1 > currentThreads_) {
			NewThread();
			std::cout << "} else if (currentThreads_ < maximumPoolSize_ && taskQueueSize_ + 1 > currentThreads_) {" << '\n';
		}

		Task newTask;
		newTask.taskFunction = taskFunction;
		newTask.arg = arg;

		while (!taskQueue_.push(newTask))
			;


	//	std::cout<<"push task ok.\n";

		++ taskQueueSize_;
		conditionVariable_.notify_one();
//		conditionVariable_.notify_all();

		std::cout<<"notify.\n";
	}

	// See: java.util.concurrent.ThreadPoolExecutor, TimeUnit: seconds 
	bool SetConfigurationInformation(long long corePoolSize, long long maximumPoolSize, long long keepAliveTime) { 
		if (0 <= keepAliveTime && 1 <= corePoolSize && corePoolSize <= maximumPoolSize) {
			corePoolSize_ = corePoolSize; 
			maximumPoolSize_ = maximumPoolSize; 
			keepAliveTime_ = keepAliveTime;
			return true;
		}
		return false;
	}

	// See: java.util.concurrent.ThreadPoolExecutor, TimeUnit: seconds 
 	void GetConfigurationInformation(long long& corePoolSize, long long& maximumPoolSize, long long& keepAliveTime) { 
		corePoolSize = corePoolSize_; 
		maximumPoolSize = maximumPoolSize_; 
		keepAliveTime = keepAliveTime_;
	}

	void NotifyAll() {
		terminateTheProcess_ = true;
		conditionVariable_.notify_all();
	}

protected:
	inline void NewThread() {
//		std::thread t(&ThreadPool::ThreadFunction, this);
		long long i = currentThreads_;
		std::thread t(&ThreadPool::ThreadFunction, this, i);

		t.detach();

		++ currentThreads_;
	}


//	void ThreadFunction() {
	void ThreadFunction(long long i) {
		std::cout<<i+1<<"外\n";

		Task t;
		bool terminateTheThread = false;
		bool enabled = false;
		//std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
		//std::chrono::duration<double> difference;

		while (!terminateTheProcess_ && !terminateTheThread) {
			do {
				std::unique_lock<std::mutex> lk(mutex_);
		//		conditionVariable_.wait_for(lk, std::chrono::seconds(1));
				if (enabled) {
					conditionVariable_.wait_for(lk, std::chrono::seconds(keepAliveTime_));
				} else {
					conditionVariable_.wait(lk);
				}
			} while(0);

			std::cout<<i+1<<".    conditionVariable_.wait(lk);→exit.\n";

			while (!terminateTheProcess_) {
				if (taskQueue_.pop(t)) {
					enabled = false;
					-- taskQueueSize_;
					t.taskFunction(t.arg);
					std::cout<<i+1<<"内\n";
				} else {
					std::cout<<i+1<<".    std::lock_guard<std::mutex> lock(terminateTheThreadMutex_);\n";
					std::lock_guard<std::mutex> lock(terminateTheThreadMutex_);
					if (currentThreads_ > corePoolSize_) {
						if (!enabled) {
							enabled = true;
						//	start = std::chrono::high_resolution_clock::now();
							std::cout<<i+1<<"退出.if (!enabled) {\n";//搜这段文本
						} else {
						//	end = std::chrono::high_resolution_clock::now();
						//	difference = end - start;
						//	std::cout<<i+1<<".    difference = end - start;\n";
						//	if (difference.count() > keepAliveTime_) { 
								-- currentThreads_;
								terminateTheThread = true;
								std::cout<<i+1<<"退出.ok.\n";
						//	}
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
	std::atomic<bool> terminateTheProcess_;
	std::atomic<long long> corePoolSize_;
	std::atomic<long long> maximumPoolSize_;
	std::atomic<long long> currentThreads_;
	std::atomic<long long> keepAliveTime_;
	std::atomic<long long> taskQueueSize_;
};
}

#endif  // THREAD_POOL_HPP 


///////////////////////////////////////////////////////////////////////////////////////////////////

// Example


//#include "threadpool.hpp"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <cstdio>

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
		ThreadPool::ThreadPool tp(123);
/*
		ThreadPool::ThreadPool tp_error(tp);
		ThreadPool::ThreadPool tp_error2(std::move(tp));

		ThreadPool::ThreadPool tp_error3(1);
		tp_error3 = tp;
		tp_error3 = std::move(tp);
*/

		long long corePoolSize, maximumPoolSize, keepAliveTime;
		std::cout << "std::thread::hardware_concurrency() = " << std::thread::hardware_concurrency() << '\n';
		std::cout << "default value:" << '\n';
		tp.GetConfigurationInformation(corePoolSize, maximumPoolSize, keepAliveTime);
		std::cout << "    corePoolSize = " << corePoolSize << ", maximumPoolSize = " << maximumPoolSize << ", keepAliveTime = " << keepAliveTime << '\n';


		for (int k = 2;k < 6;++ k) {
			switch (k) {
			case 2:
				corePoolSize    = 4;
				maximumPoolSize    = 8;
				keepAliveTime = 2;
				std::cout << "Testing: normal" << '\n';
				break;
			case 3:
				corePoolSize    = 4;
				maximumPoolSize    = 8;
				keepAliveTime = -2;
				std::cout << "Testing: 0 <= keepAliveTime" << '\n';
				break;
			case 4:
				corePoolSize    = 0;
				maximumPoolSize    = 8;
				keepAliveTime = 2;
				std::cout << "Testing: 1 <= corePoolSize" << '\n';
				break;
			case 5:
				corePoolSize    = 14;
				maximumPoolSize    = 8;
				keepAliveTime = 2;
				std::cout << "Testing: corePoolSize <= maximumPoolSize" << '\n';
				break;
			}

			if (tp.SetConfigurationInformation(corePoolSize, maximumPoolSize, keepAliveTime))
				std::cout << "    SetConfigurationInformation() return true" << '\n';
			else
				std::cout << "    SetConfigurationInformation() return false" << '\n';
			std::printf("    corePoolSize = %lld, maximumPoolSize = %lld, keepAliveTime = %lld\n", corePoolSize, maximumPoolSize, keepAliveTime);
			tp.GetConfigurationInformation(corePoolSize, maximumPoolSize, keepAliveTime);
			std::cout << "    corePoolSize = " << corePoolSize << ", maximumPoolSize = " << maximumPoolSize << ", keepAliveTime = " << keepAliveTime << '\n';
		}


//		const long SIZE = 10000;
		const long SIZE = 1000;
		long intArray[SIZE];
		int k = SIZE-10;
		for (long i = 0;i < k;++ i) {
		//	std::cout<<"main thread: tp.Execute().\n";
			intArray[i] = i;
			tp.Execute(TaskFunctionTest, &intArray[i]);
		}
		std::cout<<"before sleep(4);---------------------------------\n";
		sleep(4);
		std::cout<<"after sleep(4);---------------------------------\n";
		for (long i = k;i < SIZE;++ i) {
			intArray[i] = i;
			tp.Execute(TaskFunctionTest, &intArray[i]);
		}

		//......
		for (;;) {
			//nfds = epoll_wait(epollfd, events, MAX_EVENTS, 2000);
			if (terminateTheProcess) {
				tp.NotifyAll();
				Cleanup(); 
				break;
			}
			//......
			sleep(4);
			//kill(getpid(), SIGINT);
			kill(getpid(), SIGTERM);
			//kill(getpid(), SIGQUIT);
		}
	} while(0);

	std::cout << "cnt = " << cnt << '\n';
	return 0;
}

/*
java，线程池，thread pool
线程池，thread pool，java 
以下自用。严格来说下面对std::cout的使用是不对的。因为设置了线程数为8，所以还是可以准确判断数据的。

*/
