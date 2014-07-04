#include <ctime>
#include <chrono>

int main()
{
    for (size_t i = 0; i < 20000; i++)
#ifdef CSTYLE
        clock();
#else
        std::chrono::system_clock::now();
#endif
}