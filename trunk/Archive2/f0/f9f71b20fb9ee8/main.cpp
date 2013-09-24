#include <iostream>
using namespace std;

class X
{
private:
    struct Blah { char filler[42]; };

public:
    template< class T, class U = Blah >
    auto foo( T ) const
        -> int
    { return sizeof(U); }
};

auto main() -> int
{
    cout << X().foo( 666 ) << endl;
}
