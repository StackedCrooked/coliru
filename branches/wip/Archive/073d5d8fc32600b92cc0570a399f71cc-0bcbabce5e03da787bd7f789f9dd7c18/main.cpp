#include <array>
#include <iostream>

int main()
{
    using namespace std;

    array<bool, 3> bb = { true, false, true };
    for ( int i = 0; i < 3; i++ ) cout << static_cast<int>( bb[i] ) << endl;

    return 0;
}