#include <iostream>
#include <string>
#include <map>

struct A {
     int n { 42 };
     std::string s { "ciao" };
};

int main() {
     A a;
     auto p = std::make_pair(a.s, std::move(a));
     std::cout << "p.first: " << p.first << std::endl;
     std::cout << "p.second.s: " << p.second.s << std::endl;

     std::cout << std::endl;

     A a2;
     auto p2 = std::make_pair(std::move(a2), a2.s);
     std::cout << "p2.first.s: " << p2.first.s << std::endl;
     std::cout << "p2.second: " << p2.second << std::endl;
}
