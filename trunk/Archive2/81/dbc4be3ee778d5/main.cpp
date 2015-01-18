#include <atomic>

std::atomic<int> bar;

template <typename T>
T Dummy(const std::atomic<T>& val) { return T(); }

auto foo() -> decltype(Dummy(bar))
{
    return bar++;
}

int main()
{
    
}