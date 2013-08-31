#include <stdio.h>


namespace a {}
namespace b {}


namespace a { using namespace b; }
namespace b { using namespace a; }

namespace a { char a = 0xa; }
namespace b { char b = 0xb; }


int main()
{
    printf("%x <=> %x", a::b, b::a);
}