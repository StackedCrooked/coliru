#include <iostream>
#include <utility>
 
struct Foo {
    int n;
};
 
bool operator==(const Foo& lhs, const Foo& rhs)
{
    return lhs.n == rhs.n;
}
 
bool operator<(const Foo& lhs, const Foo& rhs)
{
    return lhs.n < rhs.n;
}
 
int main()
{
    Foo f1 = {1};
    Foo f2 = {2};
    using namespace std::rel_ops;
 
    std::cout << std::boolalpha;
    std::cout << "not equal?     : " << (f1 != f2) << '\n';
    std::cout << "greater?       : " << (f1 > f2) << '\n';
    std::cout << "less equal?    : " << (f1 <= f2) << '\n';
    std::cout << "greater equal? : " << (f1 >= f2) << '\n';
}