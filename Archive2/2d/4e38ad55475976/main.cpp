#include <vector>

void f(int&);

void test(std::vector<int>& v)
{
    for (auto it = v.begin(); it != v.end();
#if defined(USE_POSTFIX)
        it++
#else
        ++it
#endif
    )
    {
          f(*it);
    }
}
