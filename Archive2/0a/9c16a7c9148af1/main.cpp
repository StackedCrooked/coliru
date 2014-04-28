#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>
#include <mutex>
#include <atomic>
#include <thread>
#include <chrono>

#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
#define BOOST_RESULT_OF_USE_DECLTYPE
#define BOOST_THREAD_PROVIDES_FUTURE

#include <boost/thread/future.hpp>
#include <boost/thread.hpp>
using namespace std;

mutex syncio;
#define DBG(x) { lock_guard<mutex> _(syncio); cout << boolalpha << left << setw(40) << #x << (x) << endl; }

void sleep(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
}


template<typename T>
using fut = boost::future<T>;

int twice(fut<int> f){
	sleep(100);
	int current = f.get();
	DBG(current);
	return current * 2;
}

int main()
{
	try{
//		boost::packaged_task<int> pt{ []{return 2;}};

		boost::promise<int> p;

		auto p2 = std::move(p);

		p = std::move(p2);

		atomic<bool> done{false};

		/*auto f =*/ p.get_future()
				 .then(twice)
//				 .then(twice)
//				 .then(twice)
//				 .then(twice)
//				 .then(twice)
//				 .then(twice)
				 .then(twice)
				 .then(twice)
				 .then(twice)
				 .then([&](fut<int> f){
					DBG(f.get());
					done = true;
				}).then([](fut<void>){
					DBG("am I guaranteed to execute?");
				});

		thread t{
			[&](){
				this_thread::sleep_for(chrono::milliseconds(200));
//				pt();
				p.set_value(2);
			}
		};

		while(!done){
			sleep(66);
//			DBG(__LINE__);
		}

		t.join();
	}catch(std::exception& e){
		DBG(e.what());
	}
}
