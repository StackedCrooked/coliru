#include <iostream>

struct X {
    int data;
};

int main()
{
    X x1; // declare a X object
    x1.data = 500; // access the member --
                   // since x1 is not a pointer, we need to use dot . operator
                   // to access the member of x1
                   
    X* xPointer = &x1; // point xPointer to x1
    xPointer->data = 100; // access the member --
                          // since xPointer is a pointer, we need to use -> arrow
                          // operator to access the member data
                          
    // both prints "100" since xPointer points to x1
    std::cout << "x1.data : " << x1.data << '\n';
    std::cout << "xPointer->data : " << xPointer->data << '\n';
    
    // delete xPointer; is not needed since we did not dynamically allocate
}