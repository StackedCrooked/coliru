#include <atomic>
#include <utility>

std::atomic<long> bar;

template <typename T>
T Dummy(const std::atomic<T>& val) { return std::declval<T>(); }

auto foo() -> decltype(Dummy(bar))
{
    return bar++;
}

int main() {}
