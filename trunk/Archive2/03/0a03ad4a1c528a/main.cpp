
    #include <iostream>
    
    void f()
    {
        register void* foo asm ("esp");
    	std::cout << foo << '\n';
    }
    
    int main()
    {
    	register void* foo asm ("esp");
    	std::cout << foo << '\n';
    	f();
    }