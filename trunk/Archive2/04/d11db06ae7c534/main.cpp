#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <chrono>
#include <string>
#include <cstring>

#define PROFILE(BLOCK, ROUTNAME) ProfilerRun([&](){do {BLOCK;} while(0);}, \
        ROUTNAME, __FILE__, __LINE__);
//#define PROFILE(BLOCK, ROUTNAME) BLOCK

template <typename T>
void ProfilerRun (T&&  func, const std::string& routine_name = "unknown",
                  const char* file = "unknown", unsigned line = 0)
{
    using std::chrono::duration_cast;
    using std::chrono::microseconds;
    using std::chrono::steady_clock;
    using std::cerr;
    using std::endl;

    steady_clock::time_point t_begin = steady_clock::now();

    // Call the function
    func();

    steady_clock::time_point t_end = steady_clock::now();
    cerr << "[" << std::setw (20)
         << (std::strrchr (file, '/') ?
             std::strrchr (file, '/') + 1 : file)
         << ":" << std::setw (5) << line << "]   "
         << std::setw (10) << std::setprecision (6) << std::fixed
         << static_cast<float> (duration_cast<microseconds>
                                (t_end - t_begin).count()) / 1e6
         << "s  --> " << routine_name << endl;

    cerr.unsetf (std::ios_base::floatfield);
}

using namespace std;

constexpr int N = (1 << 26);
constexpr int PAGESIZE = 4096;

uint64_t __attribute__((noinline)) routine1()
{
    uint64_t sum;
    int* bigarray = new int[N];
    PROFILE (
    {
        for (int k = 0, *p = bigarray; p != bigarray+N; ++p, ++k)
            *p = k;
    }, "new (routine1)");
    sum = std::accumulate (bigarray, bigarray + N, 0ULL);
    delete [] bigarray;
    return sum;
}

uint64_t __attribute__((noinline)) routine2()
{
    uint64_t sum;
    int* bigarray = new int[N];
    
    memset(bigarray, 0, sizeof(int)*N);
    
    PROFILE (
    {
        for (int k = 0, *p = bigarray; p != bigarray+N; ++p, ++k)
            *p = k;
    }, "new + full memset (routine2)");
    sum = std::accumulate (bigarray, bigarray + N, 0ULL);
    delete [] bigarray;
    return sum;
}

uint64_t __attribute__((noinline)) routine3()
{
    uint64_t sum;
    int* bigarray = new int[N];
    
    for(int k = 0; k < N; k += PAGESIZE/2/sizeof(int))
        bigarray[k] = 0;
    
    PROFILE (
    {
        for (int k = 0, *p = bigarray; p != bigarray+N; ++p, ++k)
            *p = k;
    }, "new + strided memset (every page half) (routine3)");
    sum = std::accumulate (bigarray, bigarray + N, 0ULL);
    delete [] bigarray;
    return sum;
}

uint64_t __attribute__((noinline)) routine4()
{
    uint64_t sum;
    int* bigarray = new int[N];
    
    for(int k = 0; k < N; k += PAGESIZE/1/sizeof(int))
        bigarray[k] = 0;
    
    PROFILE (
    {
        for (int k = 0, *p = bigarray; p != bigarray+N; ++p, ++k)
            *p = k;
    }, "new + strided memset (every page) (routine4)");
    sum = std::accumulate (bigarray, bigarray + N, 0ULL);
    delete [] bigarray;
    return sum;
}

uint64_t __attribute__((noinline)) routine5()
{
    uint64_t sum;
    int* bigarray = new int[N];
    
    for(int k = 0; k < N; k += PAGESIZE*2/sizeof(int))
        bigarray[k] = 0;
    
    PROFILE (
    {
        for (int k = 0, *p = bigarray; p != bigarray+N; ++p, ++k)
            *p = k;
    }, "new + strided memset (every other page) (routine5)");
    sum = std::accumulate (bigarray, bigarray + N, 0ULL);
    delete [] bigarray;
    return sum;
}

uint64_t __attribute__((noinline)) routine6()
{
    uint64_t sum;
    int* bigarray = new int[N];
    
    for(int k = 0; k < N; k += PAGESIZE*4/sizeof(int))
        bigarray[k] = 0;
    
    PROFILE (
    {
        for (int k = 0, *p = bigarray; p != bigarray+N; ++p, ++k)
            *p = k;
    }, "new + strided memset (every 4th page) (routine6)");
    sum = std::accumulate (bigarray, bigarray + N, 0ULL);
    delete [] bigarray;
    return sum;
}

uint64_t __attribute__((noinline)) routine7()
{
    uint64_t sum;
    vector<int> bigarray (N);
    PROFILE (
    {
        for (uint64_t k = 0; k < N; ++k)
            bigarray[k] = k;
    }, "vector, using ctor to initialize (routine7)");
    sum = std::accumulate (begin (bigarray), end (bigarray), 0ULL);
    return sum;
}

uint64_t __attribute__((noinline)) routine8()
{
    uint64_t sum;
    vector<int> bigarray;
    PROFILE (
    {
        for (uint64_t k = 0; k < N; ++k)
            bigarray.push_back (k);
    }, "vector (+ no reserve) + push_back (routine8)");
    sum = std::accumulate (begin (bigarray), end (bigarray), 0ULL);
    return sum;
}

uint64_t __attribute__((noinline)) routine9()
{
    uint64_t sum;
    vector<int> bigarray;
    bigarray.reserve (N);
    PROFILE (
    {
        for (uint64_t k = 0; k < N; ++k)
            bigarray.push_back (k);
    }, "vector + reserve + push_back (routine9)");
    sum = std::accumulate (begin (bigarray), end (bigarray), 0ULL);
    return sum;
}

uint64_t __attribute__((noinline)) routine10()
{
    uint64_t sum;
    vector<int> bigarray;
    bigarray.reserve (N);
    memset(bigarray.data(), 0, sizeof(int)*N);
    PROFILE (
    {
        for (uint64_t k = 0; k < N; ++k)
            bigarray.push_back (k);
    }, "vector + reserve + memset (UB) + push_back (routine10)");
    sum = std::accumulate (begin (bigarray), end (bigarray), 0ULL);
    return sum;
}

template<class T>
void __attribute__((noinline)) adjust_size(std::vector<T>& v, int k, double factor)
{
    if(k >= v.size())
    {
        v.resize(v.size() < 10 ? 10 : k*factor);
    }
}

uint64_t __attribute__((noinline)) routine11()
{
    uint64_t sum;
    vector<int> bigarray;
    PROFILE (
    {
        for (uint64_t k = 0; k < N; ++k)
        {
            adjust_size(bigarray, k, 1.5);
            bigarray[k] = k;
        }
    }, "vector + custom emplace_back @ factor 1.5 (routine11)");
    sum = std::accumulate (begin (bigarray), end (bigarray), 0ULL);
    return sum;
}

uint64_t __attribute__((noinline)) routine12()
{
    uint64_t sum;
    vector<int> bigarray;
    PROFILE (
    {
        for (uint64_t k = 0; k < N; ++k)
        {
            adjust_size(bigarray, k, 2);
            bigarray[k] = k;
        }
    }, "vector + custom emplace_back @ factor 2 (routine12)");
    sum = std::accumulate (begin (bigarray), end (bigarray), 0ULL);
    return sum;
}

uint64_t __attribute__((noinline)) routine13()
{
    uint64_t sum;
    vector<int> bigarray;
    PROFILE (
    {
        for (uint64_t k = 0; k < N; ++k)
        {
            adjust_size(bigarray, k, 3);
            bigarray[k] = k;
        }
    }, "vector + custom emplace_back @ factor 3 (routine13)");
    sum = std::accumulate (begin (bigarray), end (bigarray), 0ULL);
    return sum;
}

uint64_t __attribute__((noinline)) routine14()
{
    uint64_t sum;
    vector<int> bigarray;
    PROFILE (
    {
        for (uint64_t k = 0; k < N; ++k)
            bigarray.emplace_back (k);
    }, "vector (+ no reserve) + emplace_back (routine14)");
    sum = std::accumulate (begin (bigarray), end (bigarray), 0ULL);
    return sum;
}

uint64_t __attribute__((noinline)) routine15()
{
    uint64_t sum;
    vector<int> bigarray;
    bigarray.reserve (N);
    PROFILE (
    {
        for (uint64_t k = 0; k < N; ++k)
            bigarray.emplace_back (k);
    }, "vector + reserve + emplace_back (routine15)");
    sum = std::accumulate (begin (bigarray), end (bigarray), 0ULL);
    return sum;
}

uint64_t __attribute__((noinline)) routine16()
{
    uint64_t sum;
    vector<int> bigarray;
    bigarray.reserve (N);
    memset(bigarray.data(), 0, sizeof(bigarray[0])*N);
    PROFILE (
    {
        for (uint64_t k = 0; k < N; ++k)
            bigarray.emplace_back (k);
    }, "vector + reserve + memset (UB) + emplace_back (routine16)");
    sum = std::accumulate (begin (bigarray), end (bigarray), 0ULL);
    return sum;
}

volatile unsigned x = 0;
template<class T>
void __attribute__((noinline)) silly_branch(std::vector<T>& v)
{
    if(v.size() < v.capacity())
    {
        std::cout << "foobar!\n";
    }
    for(int i = 0; i < 5; ++i)
    {
        x = i;
    }
}

uint64_t __attribute__((noinline)) routine17()
{
    uint64_t sum;
    vector<int> bigarray(N);
    PROFILE (
    {
        for (uint64_t k = 0; k < N; ++k)
        {
            silly_branch(bigarray);
            bigarray[k] = k;
        }
    }, "vector, using ctor to initialize + silly branch (routine17)");
    sum = std::accumulate (begin (bigarray), end (bigarray), 0ULL);
    return sum;
}

template<class T, int N>
constexpr int get_extent(T(&)[N])
{  return N;  }

int main()
{
    uint64_t results[] = {routine2(),
    routine1(),
    routine2(),
    routine3(),
    routine4(),
    routine5(),
    routine6(),
    routine7(),
    routine8(),
    routine9(),
    routine10(),
    routine11(),
    routine12(),
    routine13(),
    routine14(),
    routine15(),
    routine16(),
    routine17()};
    
    std::cout << std::boolalpha;
    for(int i = 1; i < get_extent(results); ++i)
    {
        std::cout << i << ": " << (results[0] == results[i]) << "\n";
    }
    std::cout << x << "\n";
}