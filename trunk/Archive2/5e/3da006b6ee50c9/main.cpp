#include <iostream>

class base
{
    public:
    virtual void foo(int)
    {
      std::cout << "base::foo(int)" <<std::endl;  
    }
    virtual void foo(long)
    {
      std::cout << "base::foo(long)"<<std::endl;  
    }
};

class impl : public base
{
    public:
    template<typename T>
    void foo(T t) override
    {
        std::cout << "Template: " << t<<std::endl;
    }
    
    public:
    template<typename T>
    void bar(T t) override
    {
        std::cout << "bar Template: " << t<<std::endl;
    }    
};

int main() {
    // your code goes here
	
	std::cout << "Hello World"<<std::endl;
    
    impl test;
    base &btest = test;
    
    int i=1;
    long l=2;
    double d=3.0;
    
    test.foo(i);
    test.foo(l);
    test.foo(d);
    
    test.bar(i);
    test.bar(l);
    test.bar(d);
    
    btest.foo(i);
    btest.foo(l);
	
	return 0;
}
