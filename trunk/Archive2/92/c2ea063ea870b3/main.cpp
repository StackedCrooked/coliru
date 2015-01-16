#include <iostream>
#include <vector>
#include <memory>

void bad();

struct Foo {
 int member = 0;
 void method1()
 {
     member = 1;
     std::cout << member << std::endl;
     bad();
 }
 void method2() {
     member = 2;
     std::cout << member << std::endl;
 }
};

std::vector<std::unique_ptr<Foo>> v;

void bad() 
{
    v.emplace_back(std::make_unique<Foo>());
}

int main() 
{
    v.emplace_back(std::make_unique<Foo>());
 
    for (const auto &it: v)
    {
        it->method1();
        it->method2();
    }
}