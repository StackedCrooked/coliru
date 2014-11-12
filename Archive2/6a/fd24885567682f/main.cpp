
#include <iostream>
#include <type_traits>

using namespace std;

struct B1 {
    int x = 0;
};

struct B2 {
    int x = 0;
};

struct D : virtual B1, virtual B2 {
    D() {
        //cout << x << endl; // fails to compile
        cout << B2::x << endl;
    }
};

int main()
{
    D d;
}