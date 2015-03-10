#include <iostream>
#include <chrono>
//#include <ctime>
 
long fibonacci(unsigned n)
{
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}
 
int main()
{
    std::chrono::time_point<std::chrono:: high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    std::cout << "f(42) = " << fibonacci(42) << '\n';
    end = std::chrono::high_resolution_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::high_resolution_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}