#include <utility>


#define ALIAS(A, B) \
    template<typename ...Args> auto B(Args&& ...args) { \
        return A(std::forward<Args>(args)...); \
    }


int foo(char) { return 23; }


ALIAS(foo, bar)


int main()
{
    return bar('a');
}