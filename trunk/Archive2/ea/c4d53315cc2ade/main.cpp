    #include <iostream>
    
    void foo(void (*bar)()){ bar(); };
    
    void foo()
    {
        std::cout << 5 << std::endl;
    }
    
    int main()
    { 
        foo(foo); //OK
    }