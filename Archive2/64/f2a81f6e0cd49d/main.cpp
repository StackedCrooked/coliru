#include <cassert>
#include <string>

struct S { int a; std::string b; };
struct S2 { int a; };

int main()
{
    assert( S().a == 0 );
    assert( S2().a == 0 );
}