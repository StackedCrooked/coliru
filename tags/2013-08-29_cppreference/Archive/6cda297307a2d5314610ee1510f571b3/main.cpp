#include <iostream>
#include <thread>
#include <future>
#include <time.h>
#include <stdio.h>

using namespace std;

int fib(int n)
{
    if (n <= 1) return n;
    int fib2;
    auto fib1 = async([=]{return fib(n-1);});
    fib2 = fib(n-2);
    return fib1.get() + fib2;
}

int fibrec(int n)
{
    if (n <= 1) return n;
    return fibrec(n-1) + fibrec(n-2);  
}

int main()
{
    clock_t clk1 = clock();
    cout << fib(11) << endl;
    clock_t clk2 = clock();
    cout << fibrec(11) << endl;
    clock_t clk3 = clock();
    printf("clocks for fib: %2.12e\n", (clk2 - clk1));
    printf("clocks for fib recursive: %2.12e\n", (clk3 - clk2));
}