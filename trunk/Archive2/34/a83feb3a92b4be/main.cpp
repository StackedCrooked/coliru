#include <vector>
struct Buffer : std::vector<unsigned char>{};
Buffer &operator+=(Buffer &a, Buffer const &b);

namespace Bar
{
     struct Qux { };
     Qux &operator+=(Qux &a, Qux const &b);
}

namespace Bar
{
    void foo()
    {
        Buffer a, b;
        a += b;       // error
    }
 }
 
int main()
{
    Bar::foo();
}
