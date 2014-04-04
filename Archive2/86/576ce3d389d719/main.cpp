#include <utility>
#include <vector>

struct Foo {
    template <class T>
    Foo(T) {}
};

void bar()
{
    std::vector<int> vec;
    auto func = [vec{std::move(vec)}] () { };
    Foo f1 { func};  // compile
    Foo f2 { [vec] () { } }; // compile
    Foo f3 { [vec{std::move(vec)}] () {} }; // failed to compile
}
    
int main() {

}