#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <iostream>
#include <vector> 
 void f()
 {
     std::this_thread::sleep_for(std::chrono::seconds(3));
     std::cout << "ffff" << std::endl;
 }
 void g()
 {
      //   std::this_thread::sleep_for(std::chrono::seconds(10));
     std::cout << "gggg" << std::endl; 
 }
std::vector<std::future<void>> v;
int main()
{
    
    auto f1 = std::async(std::launch::async, []{ f(); });
    v.push_back(std::move(f1));
    auto f2 = std::async(std::launch::async, []{ g(); });  // does not run until f() completes
}

