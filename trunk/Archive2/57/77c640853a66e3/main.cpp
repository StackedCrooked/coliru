#include <type_traits>
using std::is_same;

static_assert(!is_same<char, signed char>(), "");
static_assert(!is_same<char, unsigned char>(), "");
static_assert(!is_same<unsigned char, signed char>(), "");


static_assert( is_same<short, signed short>(), "");
static_assert( is_same<int, signed int>(), "");
static_assert( is_same<long, signed long>(), "");
static_assert( is_same<long long, signed long long>(), "");

static_assert(!is_same<short, unsigned short>(), "");
static_assert(!is_same<int, unsigned int>(), "");
static_assert(!is_same<long, unsigned long>(), "");
static_assert(!is_same<long long, unsigned long long>(), "");

static_assert( is_same<unsigned int, unsigned>(), "");
static_assert( is_same<short int, short>(), "");
static_assert( is_same<long int, long>(), "");
static_assert( is_same<long long int, long long>(), "");

int main(){}
