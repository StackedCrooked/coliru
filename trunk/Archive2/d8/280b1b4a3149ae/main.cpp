#include <iostream>
#include <thread>
#include <atomic>

auto order = std::memory_order_seq_cst;
std::atomic_bool value{false};

int main() {
    std::thread a([] {
        value.store(true, order);
        while(true) {}
    }), b([] {
        while(!value.load(order)) {}
        std::cout << "Got it!\n";
    });

    a.detach();
    b.join();
}