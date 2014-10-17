#include <iostream>
#include <boost/optional/optional.hpp>

using namespace std;

struct Foo {
    int GetModuleNumber() { return 5; }   
};

int main () {
    boost::optional<Foo> foo = Foo();
    cout << foo->GetModuleNumber() << endl;
}
