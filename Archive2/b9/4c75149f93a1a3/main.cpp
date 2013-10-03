#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

// ====
class Bar
{
public:
    void bar(){ cout << "Hell yeah!" << endl; }
    void foo(string a, string b){ cout << a << ", " << b << endl; };
};
// ====

void cb( void *o )
{
    if(nullptr != o)
    {
        auto f = static_cast< function<void()>* >(o);
        (*f)();
    }
}

int main()
{
    Bar b;
    function<void()> f1 = bind(&Bar::bar, &b);
    cb(&f1);
    function<void()> f2 = bind(&Bar::foo, &b, "pippo", "pluto");
    cb(&f2);
}
