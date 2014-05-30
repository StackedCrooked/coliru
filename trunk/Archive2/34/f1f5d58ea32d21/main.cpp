#include <functional>
#include <iostream>
#include <thread>

struct Foo
{
    int x, *ptr;
    std::thread thread;

    Foo(int x) :
        x(x)
    {
        ptr = &this->x;
    }
        
    void print(volatile int * ov=nullptr)
    {
        volatile int * temp = nullptr;

        if (ov != nullptr)  temp = ov;
        else                temp = this->ptr;

        std::cout << *temp << std::endl;
    }

    void print_thread(volatile int * ov)
    {
        std::thread (&Foo::print, this, ov).join ();
    }
    
    ~Foo()
    { }

};

int main(void)
{   
    int x = 12;
    Foo f{5};

    f.print_thread(&x);         // prints 12
    f.print_thread(nullptr);    // prints 5
    f.print_thread(&f.x);       // prints 5
};
