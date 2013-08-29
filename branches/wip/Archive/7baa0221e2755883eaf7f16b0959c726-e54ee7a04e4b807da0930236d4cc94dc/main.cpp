#include <stdio.h>

namespace a {}
namespace b {}

namespace a { using namespace b; }
namespace b { using namespace a; }

namespace a { char a = 'a'; }
namespace b { char b = 'b'; }

int main()
{
    printf("%c", b::a);
    printf("%c", a::b);
}
