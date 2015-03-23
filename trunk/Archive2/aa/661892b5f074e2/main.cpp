#include <stdio.h>

struct base_type {
}; /* struct base_type */

class type {
public:
    type()
        : ptr_(nullptr)
    {
    }

    type(const base_type& other)
        : ptr_(const_cast<base_type*>(&other))
    {
    }

    void print()
    {
        printf("@%p\n", ptr_);
    }

private:
    base_type* ptr_;    
}; /* class type */

int main(int argc, char* argv[])
{
    type i1;
    i1.print();
    
    base_type base;
    type i2(base);
    i2.print();
    
    base_type* dummy = reinterpret_cast<base_type*>(0x12345678);
    type i3(*dummy);
    i3.print();

    return 0;
}
