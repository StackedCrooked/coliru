#include <iostream>
struct test {
    virtual bool result() = 0;
    virtual test& self() = 0;
};
struct derived : test {
    virtual auto self() { return *this; }
    virtual bool result() { return true; }
};
bool f(test& t) {
    return t.self().result();
}
int main() {
    derived d;
    std::cout << std::boolalpha << f(d);
}