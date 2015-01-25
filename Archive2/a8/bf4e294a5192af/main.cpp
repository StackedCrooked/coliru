#include <iostream>

/// C-style function pointer
typedef void (*fp)(int * x, void * v);


/// cpp class
struct foo
{
    fp f;
    
    foo()
    {
        f = [this](int * x, void * v)
        {
            memfn();
        }      
    } 
    
    void memfn()
    {
        std::cout << "foo::memfn\n";
    }
};

int main(void)
{
    foo f;   
}
