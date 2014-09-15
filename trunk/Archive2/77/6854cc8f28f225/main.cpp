// change to 0 for successful compilation
#define WRONG 1

#if !WRONG
#include <type_traits>
#endif

typedef int (*F)();

#if WRONG
typedef typename result_of<F()>::type MyInt;
#else
typedef typename std::result_of<F()>::type MyInt;
#endif

int main () { 
}