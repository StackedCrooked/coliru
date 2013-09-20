#include <iostream>
#include <vector>
#include <chrono>

std::vector<char> f1()
{
    std::vector<char> vec;
    vec.emplace_back('a');
    vec.emplace_back('b');
    vec.emplace_back('c');
    vec.emplace_back('\0');
    return vec;
}

struct test
{
std::vector<char> f2()
{
    vec.clear();
    vec.emplace_back('a');
    vec.emplace_back('b');
    vec.emplace_back('c');
    vec.emplace_back('\0');
    return vec;
}
std::vector<char> vec;
};

int main ()
{
typedef std::chrono::high_resolution_clock clock;
typedef std::chrono::duration<float, std::milli> milli;
auto t0 = clock::now();
std::vector<char> v;
#if VER==1
for (int i = 0; i < 100000; ++i)
{
    v = f1();
}
#elif VER==2
test t;
for (int i = 0; i < 100000; ++i)
{
    v = t.f2();
}
#endif
auto t1 = clock::now();
std::cout << &v[0] << std::endl;
std::cout << milli(t1-t0).count() << "ms\n";
}