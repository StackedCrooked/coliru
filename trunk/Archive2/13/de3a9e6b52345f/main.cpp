#include <iostream>
#include <memory>
#include <string>

typedef std::string MyType;

class Base {
public:
    Base(std::unique_ptr<MyType>&& new_p) : p(std::move(new_p)) {} 
    std::unique_ptr<MyType> p;
};

std::unique_ptr<MyType> f() { return std::unique_ptr<MyType>(new std::string("goodbye world!")); }

int main()
{
    std::unique_ptr<MyType> p{new std::string("hello world!")};
	Base b(std::move(p));
	std::cout << *b.p << '\n';
    
    Base b2(f());  // works on temporaries without std::move
    std::cout << *b2.p << '\n';
}