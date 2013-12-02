#include <string>

struct String {
    std::string s;
    operator std::string() const {return s;}
};

struct Foo {
    Foo(const std::string &){}
};

void foo(Foo) {}

int main() {
    String s;
    foo(static_cast<std::string>(s));
    foo(s);
}