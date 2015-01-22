#include <iostream>
#include <chrono>
#include <ctime>
 
long sum_recursive(unsigned n)
{
    if (n == 1) return n;
    return sum_recursive(n-1) + n;
}

long sum_loop(unsigned n)
{
    long sum = 0;
    for (unsigned i = 0; i <= n; ++i) {
        sum += i;
    }
    return sum;
}
 
int main()
{
    {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    std::cout << "sum_recursive(100) = " << sum_recursive(100) << '\n';
    end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
 
    std::cout << "sum_recursive elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    std::cout << "sum_loop(100) = " << sum_loop(100) << '\n';
    end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
 
    std::cout << "sum_loop elapsed time: " << elapsed_seconds.count() << "s\n";
    }
}