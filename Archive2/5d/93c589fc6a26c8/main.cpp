#include <chrono>

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    // ...

    auto end   = std::chrono::high_resolution_clock::now();

    auto mseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}
