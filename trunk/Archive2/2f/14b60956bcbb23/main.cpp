#include <cassert>

int main()
{
    const char* a = { "Hello" };
    assert( a == "Hello" );
    const char* b = { +"Hello" };
}