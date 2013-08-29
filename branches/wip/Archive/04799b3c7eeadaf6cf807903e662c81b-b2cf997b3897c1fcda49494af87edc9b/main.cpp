#include <utility>


#define ALIAS(A, B) \
    template<typename ...Args> auto B(Args&& ...args) { \
        return A(std::forward<Args>(args)...); \
    }


struct Foo { int operator()(char) const { return 23; } };


ALIAS(Foo(), bar)


int main()
{
    return bar('a');
}