#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <functional>
#include <type_traits>
#include <ctime>
#include <ratio>
#include <chrono>

int main ()
{
  using namespace std::chrono;

    std::chrono::milliseconds when_(1000);
    std::chrono::milliseconds period_;

  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  high_resolution_clock::time_point start = t1 + when_;
  
  duration<double> t1_span = duration_cast<duration<double>>(t1-start);
  duration<double> start_span = duration_cast<duration<double>>(start);
  
  std::cout << "t1    : " << t1_span.count() << std::endl;
  std::cout << "start : " << start_span.count() << std::endl;
  
  std::cout << "printing out 1000 stars...\n";
  for (int i=0; i<1000; ++i) std::cout << "*";
  std::cout << std::endl;

  high_resolution_clock::time_point t2 = high_resolution_clock::now();

  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

  std::cout << "It took me " << time_span.count() << " seconds.";
  std::cout << std::endl;

  return 0;
}
