#include <iostream>
#include <type_traits>

#ifdef DOESNT_EXIST
namespace foo
{
    static bool const exists = false;
}
#else
namespace foo
{
    static bool const exists = true;
    class my_type { /* ... */ };
}
#endif

namespace foo { class my_type; }
using my_type = std::conditional<foo::exists, foo::my_type, void>::type;

int main(int argc, const char *argv[])
{
    std::cout << std::is_same<my_type, void>::value << std::endl;
    std::cout << std::is_same<my_type, foo::my_type>::value << std::endl;
}
