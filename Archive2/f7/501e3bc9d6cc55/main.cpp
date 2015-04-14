#include <memory>
#include <iostream>

using namespace std;

class Foo {
public:
    Foo() {
        cout << "Constructing" << endl;
    }

    ~Foo() {
        cout << "Destructing" << endl;
    }
};

void g(shared_ptr<Foo> foo)
{
    cout << "I also have a Foo with refcount " << foo.use_count() << endl;
}

void f(shared_ptr<Foo> foo)
{
    cout << "I have a Foo with refcount " << foo.use_count() << endl;
    g(foo);
}

int main()
{
    shared_ptr<Foo> foo(new Foo());
    cout << "Here the refcount is " << foo.use_count() << endl;
    f(foo);
    cout << "Here the refcount is again " << foo.use_count() << endl;
    cout << "So here it will go out of scope and reach 0" << endl;
    return 0;
}
