
#include <iostream>
#include <type_traits>

class Foo
{
    friend void freeFoo(Foo*);
public:
    Foo()
    {}
private:
    ~Foo()
    {}
};

void freeFoo(Foo* f)
{
    delete f;  // deleting a foo is fine here because of friendship
}

int main()
{
    Foo* f = new Foo();
    // delete f;   // won't compile: ~Foo is private
    freeFoo(f);    // fine because of friendship
    
    if(!std::is_constructible<Foo>::value)
    {
        std::cout << "is_constructible failed" << std::endl;
    }
}
