#include <future>
#include <iostream>

int sum(int a, int b)
{
    return a + b;
}

int main()
{
    // call 'sum()' asynchronously
    std::future<int> future_sum = std::async(std::launch::async, sum, 3, 4);
    
    // wait for the operation to finish
    future_sum.wait();
    
    // print the result
    std::cout << future_sum.get() << std::endl;
}