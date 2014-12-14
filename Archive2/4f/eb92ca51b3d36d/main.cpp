#include <iostream>
struct Foo {
    int n;
    Foo() {
       std::cout << "Enter n: "; // no flush needed
       std::cin >> n;
    }
};
Foo f; // static object
int main()
{
    std::cout << "f.n is " << f.n << '\n';
}