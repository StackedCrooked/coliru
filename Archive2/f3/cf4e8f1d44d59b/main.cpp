    #include <iostream>
 
    struct B{ };
    
    struct A
    {
        A(int, B){ std::cout << "A(int, B)" << std::endl; }
    };
    
    A a({4,B()});
    
    int main(){ }