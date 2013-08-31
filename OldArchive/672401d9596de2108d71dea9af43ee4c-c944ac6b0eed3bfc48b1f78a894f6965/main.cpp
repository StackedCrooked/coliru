#include <iostream>
#include <vector>

using namespace std;

class Foo {
public:
    Foo() {}
    Foo(const Foo&){cout << "constructed by lvalue reference." <<endl; }
    Foo(Foo&&) {cout << "constructed by rvalue reference." << endl; }
};

int main()
{
    vector<Foo> vf;
    cout << "capacity: " << vf.capacity() << endl;

    cout << "Insert a temporary." << endl;
    vf.emplace_back(Foo{});
    cout << "capacity: " << vf.capacity() << endl;

    Foo foo{};
    cout << "Insert a variable." << endl;
    vf.emplace_back(foo);
    cout << "capacity: " << vf.capacity() << endl;

    cout << "Insert a variable." << endl;
    vf.emplace_back(foo);
    cout << "capacity: " << vf.capacity() << endl;
}
