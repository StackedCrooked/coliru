#include <iostream>

struct second { char a, b; };
char f(int);
second f(bool);

template<typename T, bool hasCpp0x>
struct Yield {
    static const bool dummy = false;
};

template<typename T>
struct Yield<T, true> {
    typedef T dummy;
};

template<typename T, bool isCpp11>
struct Select {
    template<bool> struct apply {
        typedef const T& type;  
    };
};

template<typename T>
struct Select<T, true> {
    template<typename F> struct apply;
    template<typename P> struct apply<bool(P)> {
        typedef P type;  
    };
};

static const bool n = false;

#define GiveMoveOrCopyRef(T) \
    Select<T, (__cplusplus > 199711L)> \
      ::apply<bool(Yield<T, (__cplusplus > 199711L)>::dummy &&(n))>::type
    
int main() {
    int y = 0;
    GiveMoveOrCopyRef(int) x = y;
}