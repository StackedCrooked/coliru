#include <iostream>
#include <string>
#include <vector>

class Foo {
    public:
    int x = 5;
    
    void Bar() {
        std::cout << "Hello World !! \n";
    }
    
    void Baz() {
        std::cout << "x = " << x << std::endl;
    }
};

int main()
{
    Foo* foo = nullptr;
    foo->Bar();
    //foo->Baz();
}
