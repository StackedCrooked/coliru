#include <iostream>
using namespace std;

struct Foo
{
    int x;
    double y;

    // optional:
    char z;
};

int main()
{
    auto a = Foo{1, 0.1}, b = Foo{2, 1.5, 'a'};
    cout << a.x << " " << a.y << " " << b.z << endl;
}