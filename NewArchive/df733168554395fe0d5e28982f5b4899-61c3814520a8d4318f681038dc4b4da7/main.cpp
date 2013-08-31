#include <future>
#include <iostream>

int main() {
   std::cout << "doing the test" << std::endl;
   std::promise<bool> mypromise;
   std::future<bool> myfuture = mypromise.get_future();
   mypromise.set_value(true);
   bool result = myfuture.get();
   std::cout << "success, result is " << result << std::endl;
   return 0;
}