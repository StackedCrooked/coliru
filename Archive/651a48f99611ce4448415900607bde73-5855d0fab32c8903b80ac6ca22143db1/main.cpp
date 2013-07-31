#include <atomic>

std::atomic<int> x, y;
int r1, r2;

void thread1() {
    x.store(1, std::memory_order_release);
    r1 = y.load(std::memory_order_relaxed);
}

void thread2() {
    y.store(1, std::memory_order_release);
    r2 = x.load(std::memory_order_relaxed);
}
