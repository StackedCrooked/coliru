#include <atomic>
#include <iostream>

int main()
{
    std::atomic_bool obj(true);
    std::printf("%d\n", obj.load());
    std::atomic_init(&obj, false);
    std::printf("%d\n", obj.load());
}
