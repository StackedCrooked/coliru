#include <iostream>

template<uint64_t Begin, uint64_t End, template<uint64_t> class Func>
struct static_for
{
    static void exec()
    {
        Func<Begin>{}();
        static_for<Begin + 1, End, Func>::exec();
    }
};

template<uint64_t I, template<uint64_t> class Foo>
struct static_for<I, I, Foo>
{
    static void exec()
    {
    }
};

template<uint64_t I>
struct foo
{
    void operator()()
    {
        std::cout << I * 2 << std::endl;
    }
};

int main()
{
    static_for<0, 256, foo>::exec();
}
