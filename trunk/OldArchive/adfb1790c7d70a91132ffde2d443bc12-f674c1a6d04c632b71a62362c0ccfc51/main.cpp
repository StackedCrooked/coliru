#include <iostream>
#include <iomanip>
#include <algorithm>
#include <thread>
#include <mutex>
#include <future>
#include <functional>
#include <limits>
#include <boost/version.hpp>

//const unsigned long long cntSteps = std::numeric_limits<unsigned long long>::max();
const unsigned long long cntSteps = 5000000;
std::mutex lock;
   
auto pi_parallel = [](unsigned long long start, unsigned long long end, long double& result)
{
   long double sum = 0.0;
   long double x = 0.0;
   for (auto i = start; i < end; ++i)
   {
      x = (i + 0.5) / cntSteps;
      sum += 4.0 / (1.0 + x * x);
   }
   std::lock_guard<std::mutex> locker(lock);
   result += sum;
};

int main()
{
   std::cout << BOOST_VERSION << std::endl;
   std::cout << __VERSION__ << std::endl;
    
   const long double PI25DT = 3.141592653589793238462643;
   long double step = 1.0/static_cast<long double>(cntSteps);
   
   std::vector<std::thread> threads(std::thread::hardware_concurrency());
   long double sum = 0.0;
   std::cout<<"threads = "<<threads.size()<<"\n";
   unsigned long long stepsForThread = cntSteps / threads.size();
   unsigned long long start = 0;
   for (size_t i = 0; i < threads.size()-1; ++i)
   {
      threads[i] = std::thread(pi_parallel, start, start + stepsForThread, std::ref(sum));
      start += stepsForThread;
   }
   threads.back() = std::thread(pi_parallel, start, cntSteps, std::ref(sum));
   
   for (auto& t : threads) t.join();
   
   long double pi = sum / cntSteps;
   std::cout<<"The value of PI is "<<std::setprecision(20)<<pi<<"\nError is "<<fabs(pi - PI25DT) << "\n";
   
   std::cout<<'\n';
   return 0;
}

