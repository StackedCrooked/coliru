#include <vector>
#include <iostream>
#include <thread>
#include <atomic>
 
std::atomic<int> cnt = {0};
 
void f()
{
    for (int n = 0; n < 100; ++n) {
        cnt.fetch_add(1, std::memory_order_relaxed);
    }
    std::cout << "TEST" << std::endl;
}
 
int main()
{
    int cnt = 0;
    for(int i = 0;i < 10;i++)cnt += i;
    std::cout << cnt << std::endl;
}