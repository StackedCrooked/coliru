#include <iostream>
#include <string>
#include <vector>

typedef int Type;

Type myFunction();

namespace foo {

class Foo
{
 public:
    friend Type ::myFunction();

 private:
    void bar() {}
};

}

Type myFunction()
{
    foo::Foo a;
    a.bar();
    return 0;
}

int main()
{
}
