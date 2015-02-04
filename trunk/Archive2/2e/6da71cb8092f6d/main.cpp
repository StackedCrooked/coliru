#include <iostream>
#include <string>
#include <functional>

class Foo{
public:
    void bar(){
        bar([](){ return std::string("Hello"); });
    }
    void bar(std::function<std::string()> stuffer){
        std::cout << stuffer()  << " world" << std::endl;
    }
};

int main()
{
    Foo foo;
    foo.bar();
}
