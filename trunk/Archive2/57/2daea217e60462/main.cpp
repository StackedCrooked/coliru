#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>
 
void task_lambda()
{
    std::packaged_task<int(int,int)> task([](int a, int b) {
        return std::pow(a, b); 
    });
    std::future<int> result = task.get_future();
 
    task(2, 9);
 
    std::cout << "task_lambda:\t" << result.get() << '\n';
}
 
void task_bind()
{
    std::packaged_task<double()> task(std::bind(static_cast<double(*)(double, double)>(std::pow), 2, 11));    
    std::future<double> result = task.get_future();
 
    task();
 
    std::cout << "task_bind:\t" << result.get() << '\n';
}
 
void task_thread()
{
    std::packaged_task<double(double,double)> task(static_cast<double(*)(double, double)>(std::pow));
    std::future<double> result = task.get_future();
 
    std::thread task_td(std::move(task), 2, 10);
    //task_td.join();
 
    std::cout << "task_thread:\t" << result.get() << '\n';
    task_td.join();
}
 
int main()
{
    task_lambda();
    task_bind();
    task_thread();
}