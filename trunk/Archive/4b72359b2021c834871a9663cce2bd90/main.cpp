#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <chrono>
#include <cxxabi.h> // for demangler

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
        int result;
        memcpy(&result, data, sizeof(result));
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
        int result;
        std::copy(data, data + sizeof(int), reinterpret_cast<char *>(&result));
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


std::string demangle(const char * name)
{
    int st;
    char * const p = abi::__cxa_demangle(name, 0, 0, &st);

    switch (st)
    {
        case 0:  return std::shared_ptr<const char>(p, std::free).get();
        case -1: throw std::runtime_error("A memory allocation failure occurred.");
        case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
        case -3: throw std::runtime_error("One of the arguments is invalid.");
        default: throw std::runtime_error("Unexpected demangle status");
    }
}


//! Benchmarks the time required to parse the binary data.
//! Returns time elapsed in milliseconds.
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
    return static_cast<unsigned>(0.5 + 1000.0 * sw.elapsed());
}

template<typename Function>
void print_time(const Function & function, unsigned & counter)
{
    auto elapsedMs = benchmark(function, counter);
    auto functionName = demangle(typeid(Function).name());
    std::cout << functionName << std::setw(18 - functionName.size()) << elapsedMs << " ms" << std::endl;
}

int main()
{
    srand(time(0));

    // The counter is introduced to prevent the compiler
    // from optimizating *everything* away.
    unsigned counter = 0;

    // Print the times for the different strategies.
    print_time(test_cast(),     counter);
    print_time(test_memcpy(),   counter);
    print_time(test_memmove(),  counter);
    print_time(test_std_copy(), counter);

    // Printing the counter to stdout prevents the compiler from
    // optimizing away the inner loop of the benchmark function.
    std::cout << "(counter:  " << counter << ")" << std::endl << std::endl;

}
