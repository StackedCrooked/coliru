#include <thread>
#include <cstdio>

int main() {
    struct S {
        unsigned a : 10;
        unsigned :0;
        unsigned b : 10;
        struct { unsigned c : 10; } xx;
    } s = {};

    std::thread a([&s] { for (int i = 0; i < 1'000'000; ++i) { ++s.a; } });
    std::thread b([&s] { for (int i = 0; i < 1'000'000; ++i) { ++s.b; } });
    std::thread c([&s] { for (int i = 0; i < 1'000'000; ++i) { ++s.xx.c; } });
    
    a.join();
    b.join();
    c.join();

    std::printf("%u %u %u\n", s.a, s.b, s.xx.c);
}
