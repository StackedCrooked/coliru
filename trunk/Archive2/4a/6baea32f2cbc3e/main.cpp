#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
 
std::atomic<bool> lock(false); // holds true when locked
                               // holds false when unlocked
 
void f(int n)
{
    for (int cnt = 0; cnt < 100; ++cnt) {
        while(std::atomic_exchange_explicit(&lock, true, std::memory_order_acquire))
             ; // spin until acquired
        std::cout << "Output from thread " << n << '\n';
        std::atomic_store_explicit(&lock, false, std::memory_order_release);
    }
}
int main()
{
    std::vector<std::thread> v;
    for (int n = 0; n < 10; ++n) {
        v.emplace_back(f, n);
    }
    for (auto& t : v) {
        t.join();
    }
}