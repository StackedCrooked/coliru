#include <iostream>
#include <string>
#include <vector>

class Foo{
public:
    void bar(){
        bar("Hello");
    }
    void bar(std::string stuff){
        std::cout << stuff  << " world" << std::endl;
    }
};

int main()
{
    Foo foo;
    foo.bar();
}
