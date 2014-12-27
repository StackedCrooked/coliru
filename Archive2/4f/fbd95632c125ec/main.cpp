#include <iostream>
#include <memory>
 
struct Foo {
    int n1;
    int n2; 
    Foo(int a, int b) : n1(a), n2(b) {}
};
int main()
{   
    auto p1 = std::make_shared<Foo>(1, 2);
    std::shared_ptr<int> p2(p1, &p1->n1);
    std::shared_ptr<int> p3(p1, &p1->n2);
 
    std::cout << std::boolalpha
              << "p2 < p3 " << (p2 < p3) << '\n'
              << "p3 < p2 " << (p3 < p2) << '\n'
              << "p2.owner_before(p3) " << p2.owner_before(p3) << '\n'
              << "p3.owner_before(p2) " << p3.owner_before(p2) << '\n';
 
    std::weak_ptr<int> w2(p2);
    std::weak_ptr<int> w3(p3);
    std::cout 
//              << "w2 < w3 " << (w2 < w3) << '\n'  // won't compile 
//              << "w3 < w2 " << (w3 < w2) << '\n'  // won't compile
              << "w2.owner_before(w3) " << w2.owner_before(w3) << '\n'
              << "w3.owner_before(w2) " << w3.owner_before(w2) << '\n';
 
}