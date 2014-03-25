#include <iostream>

#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
#include <boost/thread/future.hpp>

struct Foo {
   boost::future<int> start() { return p.get_future(); }
   void finish() { p.set_value(23); }
 private:
   boost::promise<int> p;
};

int main () {
   Foo foo;

   auto f1 = foo.start();
   auto f2 = f1.then([](boost::future<int> f) {
      std::cout << "done:" << std::endl;
      std::cout << f.get() << std::endl;
   });

   foo.finish();
   f2.get();
}
