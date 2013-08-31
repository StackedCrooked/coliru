#include <iostream>
#include <algorithm>
#include <functional>
#include <chrono>
#include <vector>

using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

void timeit(std::function<void()>);

void timeit(std::function<void()> f)
{
        
    std::vector<milliseconds> executionDurations(10,milliseconds::zero() );
    
    // Form vector of 10 timings of function we are timing
    for ( auto thisDuration = executionDurations.begin(); thisDuration != executionDurations.end(); ++thisDuration) {
    
        steady_clock::time_point start = steady_clock::now();
    
        // Evaluate function that we want to time
        f();
    
        steady_clock::time_point end = steady_clock::now();
        
        *thisDuration = duration_cast<milliseconds>(end - start);
    
    }
    
    // Use std::accumulator to form arithmetic mean of durations
    std::chrono::milliseconds meanDuration = accumulate(executionDurations.begin(), executionDurations.end(), milliseconds::zero() ) / executionDurations.size();
    std::cout << "Mean execution time: " << meanDuration.count() << " us." << std::endl;
    
}

void somethingThatIWantToProfile(void)
{
    
    // Elementwise add one million elements.
    std::vector<double> foo(1000000,0);
    std::vector<double> bar = foo;
    std::vector<double> mySum(1000000,0);
    
    std::transform(foo.begin(),foo.end(),bar.begin(),mySum.begin(),std::plus<double>());
 
}


int main(int argc, const char * argv[])
{
    
    // Wrap whatever we want to profile into a lambda
    auto myLambda = [] { somethingThatIWantToProfile(); };
    // Pass our lambda to the timeit function.
    timeit(myLambda);
    
    return 0;
}