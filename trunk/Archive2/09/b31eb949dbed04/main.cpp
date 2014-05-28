#include <iostream>
#include <utility>

#define APIENTRY
using UINT = unsigned;

typedef UINT(APIENTRY *PFNFOO)(UINT, double);

class Foo
{
public:
    static UINT APIENTRY pfnFoo(UINT x, double y)
    {
        return (UINT)(x*y);
    }
};

template<typename RET, typename... ARGS>
inline RET CallFunc(RET(*pfn)(ARGS...), ARGS&&... args)
{
    return (*pfn)(std::forward<ARGS>(args)...);
}

int main()
{
    std::cout << CallFunc(&Foo::pfnFoo, 100U, 0.5) << std::endl;
    std::cout << CallFunc<UINT, UINT, double>(&Foo::pfnFoo, 100, 0.5f) << std::endl;
}
