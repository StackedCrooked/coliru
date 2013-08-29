#include <iostream>
#include <functional>
#include <memory>
#include <cstdint>

using namespace std;

function<uint64_t ()> makeFibonacci()
{
    auto cur = make_shared<uint64_t>(1);
    auto prev = make_shared<uint64_t>(1);
    return [=]
    {
        const auto next = *cur + *prev;
        const auto result = *prev;
        *prev = *cur;
        *cur = next;
        return result;
    };
}

void repeat(const int times, const function<void ()>& f)
{
    for(auto i = 0; i < times; ++i)
        f();
}

int main()
{
    const auto fibonacci = makeFibonacci();
    repeat(16, [&] { cout << fibonacci() << endl; });
}
