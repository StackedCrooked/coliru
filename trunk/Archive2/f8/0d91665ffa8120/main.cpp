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


#ifdef _GNU_SOURCE
#include <pthread.h>
#endif  // _GNU_SOURCE

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
		shutdownNow_ = false;
		currentThreads_ = 0;
		taskQueueSize_ = 0;
		long long hardware_concurrency = (std::thread::hardware_concurrency() == 0) ? 1 : std::thread::hardware_concurrency();
		corePoolSize_ = hardware_concurrency;
		maximumPoolSize_ = hardware_concurrency;// * 2;
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
		if (currentThreads_ < maximumPoolSize_ && taskQueueSize_ + 1 > currentThreads_) {
			NewThread();
			std::cout << "if (currentThreads_ < maximumPoolSize_ && taskQueueSize_ + 1 > currentThreads_) {" << '\n';
		}

		Task newTask;
		newTask.taskFunction = taskFunction;
		newTask.arg = arg;

		while (!taskQueue_.push(newTask))
			;

		++ taskQueueSize_;
		conditionVariable_.notify_one();
		std::cout<<"notify.\n";
	}

	void SetCorePoolSize(long long corePoolSize) { 
		corePoolSize_ = corePoolSize; 
	}

	long long GetCorePoolSize() {
		return corePoolSize_; 
	}

	// TimeUnit: milliseconds 
	void SetKeepAliveTime(long long keepAliveTime) {
		keepAliveTime_ = keepAliveTime;
	}

	// TimeUnit: milliseconds 
	long long GetKeepAliveTime() {
		return keepAliveTime_;
	}

	void SetMaximumPoolSize(long long maximumPoolSize) {
		maximumPoolSize_ = maximumPoolSize; 
	}

	long long GetMaximumPoolSize() {
		return maximumPoolSize_; 
	}

	void ShutdownNow() {
		shutdownNow_ = true;
		conditionVariable_.notify_all();
	}

	virtual bool SetAffinity(void *arg) { 
		#ifdef _GNU_SOURCE
			#define handle_error_en(en, msg) \
				do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

			int s, j;
			cpu_set_t cpuset;
			pthread_t thread;

			thread = pthread_self();

			/* Set affinity mask to include CPUs 0 to 7 */

			CPU_ZERO(&cpuset);
			for (j = 0; j < 8; j++)
				CPU_SET(j, &cpuset);

			s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
			if (s != 0)
				handle_error_en(s, "pthread_setaffinity_np");
		#endif  // _GNU_SOURCE

		return true;
	}

	virtual bool GetAffinity(void *arg) { 
		#ifdef _GNU_SOURCE

		#endif  // _GNU_SOURCE

		return true;
	}

protected:
	inline void NewThread() {
//		std::thread t(&ThreadPool::ThreadFunction, this);
		++pp;
		std::thread t(&ThreadPool::ThreadFunction, this, pp);

		t.detach();

		++ currentThreads_;
	}


//	void ThreadFunction() {
	void ThreadFunction(long long i) {
		std::cout<<i+1<<"外\n";

		//SetAffinity(NULL);

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
					if (currentThreads_ > corePoolSize_) {
						if (!enabled) {
							enabled = true;
							std::cout<<i+1<<"退出.if (!enabled) {\n";
						} else {
							-- currentThreads_;
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
	std::atomic<bool> shutdownNow_;
	std::atomic<long long> corePoolSize_;
	std::atomic<long long> maximumPoolSize_;
	std::atomic<long long> currentThreads_;
	std::atomic<long long> keepAliveTime_;
	std::atomic<long long> taskQueueSize_;
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
		ThreadPool::ThreadPool tp(123);
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
		tp.SetCorePoolSize(4);
		tp.SetMaximumPoolSize(8);
		tp.SetKeepAliveTime(2 * 1000);
		std::cout << "new value:" << '\n';
		std::cout << "    corePoolSize = " << tp.GetCorePoolSize() << ", maximumPoolSize = " << tp.GetMaximumPoolSize() << ", keepAliveTime = " << tp.GetKeepAliveTime() << " ms." << '\n';


//		const long SIZE = 10000;
		const long SIZE = 1000;
	//	const long SIZE = 100;
		long intArray[SIZE];
		for (long i = 0;i < SIZE;++ i) {
			intArray[i] = i;
			tp.Execute(TaskFunctionTest, &intArray[i]);
		}

		// ......
		// 设置cpu亲缘性
		for (;;) {
			//nfds = epoll_wait(epollfd, events, MAX_EVENTS, 2000);
			if (terminateTheProcess) {
				tp.ShutdownNow();
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
*/


