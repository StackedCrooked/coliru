//recursive condition
template<unsigned long long value, unsigned long long base=2>
struct tmp_log
{
    enum {result = tmp_log<value/base>::result + 1};
};

//end conditions
template<unsigned long long base>
struct tmp_log<1ull,base> 
{
    enum {result = 0};
};
template<unsigned long long base>
struct tmp_log<0ull,base> 
{
    enum {result = 0};
};

//double check for errors
static_assert(tmp_log<1>::result == 0, "tmp_log error");
static_assert(tmp_log<2>::result == 1, "tmp_log error");
static_assert(tmp_log<3>::result == 1, "tmp_log error");
static_assert(tmp_log<4>::result == 2, "tmp_log error");

static_assert(tmp_log<0,10>::result == 0, "tmp_log error");
static_assert(tmp_log<9,10>::result == 0, "tmp_log error");
static_assert(tmp_log<10,10>::result == 1, "tmp_log error");
static_assert(tmp_log<11,10>::result == 1, "tmp_log error");
static_assert(tmp_log<99,10>::result == 1, "tmp_log error");
static_assert(tmp_log<100,10>::result == 2, "tmp_log error");

template <unsigned long long value>
struct bits2use {
    enum { result = tmp_log<value-1>::result+1 };
};

//double check for errors
static_assert(bits2use<0>::result == 1, "bits2use error");
static_assert(bits2use<1>::result == 1, "bits2use error");
static_assert(bits2use<2>::result == 2, "bits2use error");
static_assert(bits2use<3>::result == 2, "bits2use error");
static_assert(bits2use<4>::result == 3, "bits2use error");

#include <iostream>
#ifndef NUM 
#define NUM 18 
#endif

int main()
{
   std::cout << bits2use<NUM>::result << '\n';
   return 0;
}