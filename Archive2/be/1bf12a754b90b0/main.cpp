#include <vector>
#include <map>
#include <initializer_list>

struct A
{
    A() {} 
    A(A&&) {}
    A(const A&) {}
    A(std::initializer_list<int>) {}

    void operator=(A&&) {}
    void operator=(std::initializer_list<int>) {}
};

struct B
{
    B() {}
    B(B&&) {}
    B(std::initializer_list<std::pair<int, A>>) {}

    void operator=(B&&) {}
    void operator=(std::initializer_list<std::pair<int, A>>) {}
};

struct C
{
    C() {}
    C(C&&) {}
    C(std::initializer_list<std::pair<int, A>>) {}

    void operator=(const C&) {} // Only difference from B
    void operator=(C&&) {}
    void operator=(std::initializer_list<std::pair<int, A>>){}
};

int main()
{
    std::vector<int> v;
    v = { 1, 2, 3 };            // fine

    std::map<int, int> m;
    m = { { 1, 2 } };           // ambiguous
    
    A a;
    a = { 1, 2, 3 };            // fine

    B b; 
    b = { { 1, { 1, 2 } } };    // fine

    C c;
    c = { { 1, { 1, 2 } } };    // ambiguous
}
