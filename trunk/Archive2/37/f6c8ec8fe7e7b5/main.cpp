#include <chrono>
#include <type_traits>

using Clock = std::conditional<
    std::chrono::high_resolution_clock::is_steady
    , std::chrono::high_resolution_clock
    , std::chrono::steady_clock
>::type;

template <typename Dur, typename Func>
int benchmark(Func&& func)
{
    auto start = Clock::now();
    func();
    auto stop = Clock::now();
    return std::chrono::duration_cast<Dur>(stop-start).count();
}

#include <iostream>
#include <iomanip>
#include <bitset>

using namespace std;
using namespace std::chrono;

int count_bits_naive(unsigned i)
{
    int rval = 0;
    for (; i != 0; i >>= 1)
    {
      rval += i & 1;
    }
    return rval;
}

int count_bits_kernighan(unsigned i)
{
    int rval = 0;
    for (; i != 0; ++rval)
    {
      i &= i - 1;
    }
    return rval;
}

int main()
{
    constexpr unsigned warmupVal = 0x56f47dU;
    constexpr unsigned iterations = 10000000U;
    
    int accum = 0;
    
    cout.sync_with_stdio(false);
    
    cout << "Warmup:" << endl;
    cout << "Bits in 0x"
         << hex << warmupVal << dec
         << " (" << bitset<32>(warmupVal) << "):"
    << endl;
    cout << "    Naive:     " << count_bits_naive(warmupVal) << endl;
    cout << "    Kernighan: " << count_bits_kernighan(warmupVal) << endl;
    
    cout << endl;
    
    cout << "Benchmarks:" << endl;
    
    cout << "    Naive:     " << benchmark<milliseconds>([&]{
        for (unsigned i = 0; i < iterations; ++i)
        {
            accum += count_bits_naive(i);
        }
    }) << "ms" << endl;
    
    cout << "    Kernighan: " << benchmark<milliseconds>([&]{
        for (unsigned i = 0; i < iterations; ++i)
        {
            accum += count_bits_kernighan(i);
        }
    }) << "ms" << endl;
    
    cout << "Accum: " << accum << endl;
}
