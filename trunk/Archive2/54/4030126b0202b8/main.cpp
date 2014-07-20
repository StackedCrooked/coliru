#include <iostream>

#ifdef OK
struct ostream { } cout;

bool operator<<(ostream&, const char* s)
{ __builtin_printf("%s", s); return true; }
#else
using std::cout;
#endif

struct X { int a = (cout<<"hmm\n") ? 1 : 2;};

int main()
{
    X x;
}