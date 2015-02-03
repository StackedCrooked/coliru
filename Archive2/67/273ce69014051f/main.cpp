#include <iostream>
#include <string>
#include <functional>

class Foo;

class Foo{
public:
    static std::string myFn(){
        return "Hello";    
    }
    void bar(){
        bar(myFn);
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
