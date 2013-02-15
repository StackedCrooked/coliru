#include <iostream>
#include <chrono>
#include <thread>   // simple 'sleep_for' example

#include <cstdio>   // printf

// Test cout() speeds.  Verbose version of exposing clock/time_point/duration use
double test_cout()
{
    // Grab the start point time
    std::chrono::high_resolution_clock::time_point clkStart = std::chrono::high_resolution_clock::now();
    
    // Loop prep: set boolalpha before to cut out two calls:
    std::cout << std::boolalpha;
    
    // Loop to measure
    for (int i = 1; i < 500; i++)
        std::cout << "cout_test,   bool:" << bool(i&1) << "; double:" << 1.34 << std::endl;
    
    // Loop Cleanup
    std::cout << std::noboolalpha;
    
    // Grab the end point time
    std::chrono::high_resolution_clock::time_point clkEnd = std::chrono::high_resolution_clock::now();
    
    // get the difference of the 2 times (now - clkStart), convert it into the appropriate duration type
    std::chrono::duration<double, std::milli> clkElapsed(
        std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(clkEnd - clkStart)
    );
    
    // and finally get the actual value
    double fElapsed = clkElapsed.count();
    
    return fElapsed;
}

// Test printf() speeds.  Less verbose version of exposing clock/time_point/duration use
double test_printf()
{
    // Aliases make things soo much cleaner!
    typedef std::chrono::high_resolution_clock hrClock_t;
    // duration type: calculation will be floating point, ratio will be 1/1000th (of a second)
    typedef std::chrono::duration<double, std::milli> millisecs_t;
    
    // Grab the start point time
    auto clkStart = hrClock_t::now();
    
    // Loop to measure
    for (int i = 1; i < 500; i++)
        printf("printf_test, bool:%s; double:%.02f\n", ((i&1) ? "true" : "false"), 1.34);
    
    // Grab the end point time
    auto clkEnd = hrClock_t::now();
    
    // get the difference of the 2 times (now - clkStart), convert it into the appropriate duration type
    millisecs_t clkElapsed(std::chrono::duration_cast<millisecs_t>(clkEnd - clkStart));
    
    // and finally get the actual value
    double fElapsed = clkElapsed.count();
    
    return fElapsed;
}

int main ()
{
  double fcoutTime, fprintfTime;
  
  fcoutTime = test_cout();
  
  fprintfTime = test_printf();
  
  // Random injection of a sleep (to show another use of chrono)
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  
  printf("test_cout elapsed time = %f, vs. test_printf elapsed time = %f\n", fcoutTime, fprintfTime);

  return 0;
}