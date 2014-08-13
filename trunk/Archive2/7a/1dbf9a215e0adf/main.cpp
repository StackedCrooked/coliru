#include <iostream>
#include <string>
#include <vector>

class Foo
{
    public:
    ~Foo() {
        printf("des of foo");
    }
};

int main()
{
    
    Foo *a = new Foo;
    void *b = a;
    delete (Foo *)b;
    //delete a;
}
