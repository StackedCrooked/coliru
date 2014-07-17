#include <iostream>
#include <vector>

using namespace std;

class Foo{
public:
    Foo(const Foo&) {cout << "copy ctor" << endl;}
    Foo(Foo&&) noexcept {cout << "move ctor" << endl;}
    Foo& operator=(Foo&&) noexcept {cout << "move assgn" << endl; return *this;}
    Foo() {cout << "ctor" << endl;}
    ~Foo() {cout << "dtor" << endl;}
};


int main()
{   
    Foo foo;

//    vector<Foo> v;
//    v.push_back(std::move(foo)); 

//     comment the above 2 lines and replace by
     vector<Foo> v{std::move(foo)}; 
}
