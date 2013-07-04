#include <list>
#include <iostream>

namespace test
{
    class child;
    
    class parent
    {
        public:
            
            parent()
            {
                all.push_back((child*) this);
            }
            
            ~parent()
            {
                all.remove((child*) this);
            }
            
            void foo() const
            {
                std::cout << "foo" << std::endl;   
            }
            
            static const std::list<child*>& getAll()
            {
                return all;
            }
            
        private:
        
            static std::list<child*> all;
    };
    
    std::list<child*> parent::all;
    
    class child : public parent
    {
        public:
            
            void bar() const
            {
                std::cout << "bar" << std::endl;   
            }
    };
}

int main()
{
    for (int count = 0; count < 10; count++)
    {
        new test::child();
    }
    
    std::cout << test::child::getAll().size() << std::endl;
    
    for (test::child* child : test::child::getAll())
    {
        child->foo();
        child->bar();
    }
}