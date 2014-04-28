#include <iostream>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>


class camera
{
    public:
        void foo(void){
            std::cout << "Foo on camera was called" << std::endl;
        }
    
    ~camera()
    {
       
       std::cout<<" camera's destructor was called" << std::endl;
    }
    
    
};

class B
{
    public:
    B(boost::shared_ptr<camera> cam)
    {
        a = cam;
        std::cout<<" B's constructor was called" << std::endl;
    }
    
    ~B()
    {
      a->foo();
       std::cout<<" B's destructor was called" << std::endl;
    }
    
    private:
    boost::shared_ptr<camera> a;
};

class A
{
    public:
    A()
    {
        std::cout<<" A's constructor was called" << std::endl;
    }
    
    ~A()
    {
        a->foo();
       std::cout<<" A's destructor was called" << std::endl;
    }
    
    void init(void)
    {
          a.reset(new camera());
          bInstance = new B(a);
    }
    
    private:
    boost::shared_ptr<camera> a;
    B* bInstance;
};



int main()
{
  
    A * aInstance = new A();
    aInstance->init();
    
    delete aInstance;
   
    
   std::cout << "Test complete" << std::endl;
}
