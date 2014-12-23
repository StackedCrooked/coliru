#include <iostream>

class Foo;
template<class format>
void serialize(const Foo&, std::ostream&);

class Foo {
    private:
        int age = 100;
        template<class format>
        friend void ::serialize(const Foo&, std::ostream&);
};

struct JSON {};
struct YAML {};
struct Binary {};

template<>
void serialize<JSON>(const Foo& foo, std::ostream& out) {
    out << "{ \"age\": " << foo.age << " }";
}
template<>
void serialize<YAML>(const Foo& foo, std::ostream& out) {
    out << "age: " << foo.age;
}

int main() {
    Foo test;
    //std::cout << test.age << "\n";
    serialize<JSON>(test, std::cout);
    serialize<YAML>(test, std::cout);
}