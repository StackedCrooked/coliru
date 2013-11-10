//#define NDEBUG 

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>
#include <chrono>

template<int> void asm_marker();

class Stopwatch
{
public:
    typedef std::chrono::high_resolution_clock Clock;

    //! Constructor starts the stopwatch
    Stopwatch() : mStart(Clock::now())
    {
    }

    //! Returns elapsed number of seconds in decimal form.
    double elapsed()
    {
        return 1.0 * (Clock::now() - mStart).count() / Clock::period::den;
    }

    Clock::time_point mStart;
};

struct test_cast
{
    int operator()(const char * data) const
    {
        return *((int*)data);
    }
};

struct test_memcpy
{
    int operator()(const char * data) const
    {
        asm_marker<3333>();
        int result;
        memcpy(&result, data, sizeof(result));
        asm_marker<4444>();
        return result;
    }
};

struct test_memmove
{
    int operator()(const char * data) const
    {
        int result;
        memmove(&result, data, sizeof(result));
        return result;
    }
};


struct test_std_copy
{
    int operator()(const char * data) const
    {
        asm_marker<1111>();
        int result;
        std::copy(data, data + sizeof(int), reinterpret_cast<char *>(&result));
        asm_marker<2222>();
        return result;
    }
};

enum
{
    iterations = 2000,
    container_size = 2000
};

//! Returns a list of integers in binary form.
std::vector<char> get_binary_data()
{
    std::vector<char> bytes(sizeof(int) * container_size);
    for (std::vector<int>::size_type i = 0; i != bytes.size(); i += sizeof(int))
    {
        memcpy(&bytes[i], &i, sizeof(i));
    }
    return bytes;
}

template<typename Function>
unsigned benchmark(const Function & function, unsigned & counter)
{
    std::vector<char> binary_data = get_binary_data();
    Stopwatch sw;
    for (unsigned iter = 0; iter != iterations; ++iter)
    {
        for (unsigned i = 0; i != binary_data.size(); i += 4)
        {
            const char * c = reinterpret_cast<const char*>(&binary_data[i]);
            counter += function(c);
        }
    }
    return unsigned(0.5 + 1000.0 * sw.elapsed());
}

int main()
{
    srand(time(0));
    unsigned counter = 0;

    std::cout << "cast:      " << benchmark(test_cast(),     counter) << " ms" << std::endl;
    std::cout << "memcpy:    " << benchmark(test_memcpy(),   counter) << " ms" << std::endl;
    std::cout << "memmove:   " << benchmark(test_memmove(),  counter) << " ms" << std::endl;
    std::cout << "std::copy: " << benchmark(test_std_copy(), counter) << " ms" << std::endl;
    std::cout << "(counter:  " << counter << ")" << std::endl << std::endl;

}