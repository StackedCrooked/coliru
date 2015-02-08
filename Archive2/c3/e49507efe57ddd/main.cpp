#include <iostream>
#include <string>

#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

#include <boost/thread/future.hpp>

using namespace boost;


int main() {
   future<int> f1 = async([]() { return 2; });
   future<int> f2 = f1.then([](future<int> f) { return f.get() * 3; });
   std::cout << f2.get();
}