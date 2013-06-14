#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>
#include <sys/time.h>
 
double get_current_time()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    return double (tv.tv_sec) + 0.000001 * tv.tv_usec;
}
 
int get_int_v1(const char * data) { return *reinterpret_cast<const int*>(data); }
int get_int_v2(const char * data) { int result; memcpy(&result, data, sizeof(result)); return result; }
 
const unsigned iterations = 200 * 1000 * 1000;
    
double test_v1(const char * c, unsigned & prevent_optimization)
{
    double start = get_current_time();
    for (unsigned i = 0; i != iterations; ++i)
    {
        prevent_optimization += get_int_v1(c);
    }
    return get_current_time() - start;
}
 
double test_v2(const char * c, unsigned & prevent_optimization)
{
    double start = get_current_time();
    for (unsigned i = 0; i != iterations; ++i)
    {
        prevent_optimization += get_int_v2(c);
    }
    return get_current_time() - start;
}
 
int main()
{
    srand(time(0));
    
    // Initialize data
    std::vector<int> numbers(1000);
    for (std::vector<int>::size_type i = 0; i != numbers.size(); ++i)
    {
        numbers[i] = i;
    }
    
    // Repeat benchmark 4 times.
    for (unsigned i = 0; i != 4; ++i)
    {
        unsigned p = 0;
        std::vector<int>::size_type index = rand() % numbers.size();
        const char * c = reinterpret_cast<const char *>(&numbers[index]);    
        std::cout << "index: " << index << std::endl;
        std::cout << "v1: " << test_v1(c, p) << std::endl;
        std::cout << "v2: " << test_v2(c, p) << std::endl << std::endl;
    }
}