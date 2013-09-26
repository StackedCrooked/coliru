#include <thread>
#include <cstdio> // because these are atomic

thread_local int x=0;

int main() {
    auto f = [] { std::printf("%p\n", static_cast<void*>(&x)); };
    f();
    std::thread t1{f}, t2{f};
    t1.join(); t2.join();
}