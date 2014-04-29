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

		atomic<bool> done{false};

		thread t2;

		{
			boost::promise<int> p;

			auto p2 = std::move(p);

			p = std::move(p2);


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
				[&, p = std::move(p)]() mutable {
					this_thread::sleep_for(chrono::milliseconds(200));
	//				pt();
					p.set_value(2);
				}
			};
			t2 = move(t);
		}


		while(!done){
			sleep(66);
//			DBG(__LINE__);
		}


//		while(!f.is_ready()){
//			sleep(666);
//			DBG(__LINE__);
//		}

//		int ret = f.get();

//		DBG(ret);

		t2.join();
	}catch(std::exception& e){
		DBG(e.what());
	}
}

