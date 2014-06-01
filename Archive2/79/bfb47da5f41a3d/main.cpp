#include <iostream>

uint64_t pclock()
{
    uint64_t tt;
    asm volatile (
        "rdtsc;"
        "shl $32, %%rdx;"
        "or %%rdx, %%rax;"
        :"=a"(tt)
        :
        :"%rdx"
    );
    return tt;
}

int main()
{
    {
        auto p = pclock();
        int arr[1000000];
        p = pclock() - p;
        std::cout << "Static: " << p << " processor ticks.\n";
    }
    {
        auto p = pclock();
        int* arr = new int[1000000];
        p = pclock() - p;
        std::cout << "Dynamic: " << p << " processor ticks.\n";
    }
    return 0;
}
