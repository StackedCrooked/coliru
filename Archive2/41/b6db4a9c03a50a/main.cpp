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
                   
    X* xPointer = new X; // allocate a new X
    xPointer->data = 100; // access the member --
                          // since xPointer is a pointer, we need to use -> arrow
                          // operator to access the member data
                          
    std::cout << "x1.data : " << x1.data << '\n'; // 500
    std::cout << "xPointer->data : " << xPointer->data << '\n'; // 100
    
    delete xPointer; // do not forget to delete to prevent memory leaks
}