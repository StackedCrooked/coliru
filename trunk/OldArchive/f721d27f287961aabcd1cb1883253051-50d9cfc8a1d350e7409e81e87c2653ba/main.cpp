    #include <iostream>
    
    class B;
    
    class A
    {
        B* b;    
    };
    
    class B
    {
        A* a;    
    };
    
    int main()
    {
        A a;
        B b;
    }