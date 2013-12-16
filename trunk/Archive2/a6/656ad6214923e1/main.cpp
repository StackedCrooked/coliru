#include <iostream>

struct Foo {
private:
    // Disallow the copy and default constructor as well as the assignment
    // operator
    Foo();
    Foo(Foo const & foo);
    Foo & operator = (Foo const & foo);

public:                         
    // Store a little bit of data
    int data;                   
    Foo(int const & data_) : data(data_) { }

    // Write a move constructor 
    Foo(Foo && foo) {           
        std::cout << "Move constructor" << std::endl;
        data=foo.data;          
    }                           
};                              

// Write a function that creates and returns a Foo
Foo Bar() {                     
    Foo foo(3);                 
    return foo;                 
}                               

// See if we can mix things up  
Foo Baz(int x) {                
    Foo foo2(2);                
    Foo foo3(3);   
    if (x > 2)
        return foo2;
    return foo3;
}                               

int main() {                    
    // This is using the return value optimization (RVO)
    Foo foo1 = Bar();           
    std::cout << foo1.data << std::endl;

    // This should make the RVO fail 
    Foo foo2 = Baz(3);
    std::cout << foo2.data << std::endl;
}