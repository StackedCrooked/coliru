#include <iostream>
#include <memory>
#include <boost/optional/optional.hpp>

using namespace std;

struct Foo {
    int GetModuleNumber() { return 5; }   
};

int main () {
    boost::optional<shared_ptr<Foo>> foo = make_shared<Foo>();
    cout << foo->GetModuleNumber() << endl;
}
