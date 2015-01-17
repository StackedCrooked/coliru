    #include <iostream>
    
    void foo(void (*bar)()){ bar(); };
    
    void foo(int a = 5)
    {
        std::cout << a << std::endl;
    }
    
    int main()
    { 
        foo(foo); //Error
    }