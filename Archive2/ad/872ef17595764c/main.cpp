#include <string>
#include <vector>
#include <initializer_list>
#include <memory>

struct Foo {
    Foo(std::initializer_list<std::string> strings) : strings(strings) {}
    
    std::vector<std::string> strings;
};

int main(int, char**) {
    
    auto ptr = std::make_unique<Foo>({"Hello", "World"});
    
    return 0;
}