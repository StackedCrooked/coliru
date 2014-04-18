#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>

#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
#define BOOST_RESULT_OF_USE_DECLTYPE
#define BOOST_THREAD_PROVIDES_FUTURE

#include <boost/thread/future.hpp>
#include <boost/thread.hpp>

using namespace std;

#define DBG(x) { cout << left << setw(30) << #x << (x) << endl; }

void sleep(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
}


template<typename T>
using fut = boost::future<T>;

int twice(fut<int> f){
	sleep(600);
	int current = f.get();
	DBG(current);
	return current * 2;
}

int main()
{
	try{
		boost::packaged_task<int> pt{ []{return 2;}};


		auto f = pt.get_future()
				 .then(twice)
				 .then(twice)
				 .then(twice)
				 .then(twice)
				 .then(twice)
				 .then(twice)
				 .then(twice)
				 .then(twice)
				 .then(twice);

		thread t{
			[&](){
				this_thread::sleep_for(chrono::milliseconds(2500));
				pt();
			}
		};


		while(!f.is_ready()){
			sleep(451);
			DBG(__LINE__);
		}

		int ret = f.get();

		DBG(ret);

		t.join();
	}catch(std::exception& e){
		DBG(e.what());
	}
}


