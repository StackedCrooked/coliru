#include <iostream>

#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
#include <boost/thread/future.hpp>
#include <boost/thread.hpp>

struct Foo {
   boost::future<int> start() {
      return boost::async([]{ boost::this_thread::sleep_for(boost::chrono::seconds(2)); return 89; });
   }
};

int main () {
   Foo foo;

   foo.start().then([](boost::future<int> f) {
      std::cout << "done:" << std::endl;
      std::cout << f.get() << std::endl;
   })
      .get(); // if you leave this out, either task may or may not run
}