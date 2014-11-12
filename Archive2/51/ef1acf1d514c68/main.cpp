
#include <iostream>
#include <type_traits>

using namespace std;

struct M { M(){} M(M const&) =delete; };
struct X { X(){} X(X const&) =default; M m; }; // X(X const&) is actually deleted!

int main()
{
    X x1;
    X x2(x1);
}