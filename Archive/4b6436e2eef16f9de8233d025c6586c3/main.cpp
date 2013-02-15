#include <chrono>

std::chrono::milliseconds operator"" _ms (unsigned long long value)
{
    return std::chrono::milliseconds(value);
}

int main()
{
    using sleep = std::this_thread::sleep_for;
    sleep(10_ms);
}