#include <cassert>

int main()
{
    static const char* val1 = "foobar";
	const char* val2 = "bar";
    assert(val1+3 == val2);
}