#include <atomic>

struct B {};

struct C {
    static void addB(std::atomic<B>&);
};

void C::addB(std::atomic<B>& b)
{

    B b2 = b.load();
    B newValue = B();

    bool result = b.compare_exchange_weak(b2, newValue, std::memory_order_relaxed, std::memory_order_release);

}

int main() {
    std::atomic<B> b{};
    C{}.addB(b);
}
