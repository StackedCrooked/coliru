#include <list>
#include <iostream>

namespace test
{
    class platform
    {
        public:
            
            void setSomething(int something) const
            {
                std::cout << "set something to " << something << std::endl;   
            }
    };
    
    class shared : platform
    {
        public:
            
            shared()
            {
                setSomething(666);
                
                all.push_back(this);
            }
            
            ~shared()
            {
                all.remove(this);
            }
            
            static const std::list<shared*>& getAll()
            {
                return all;
            }
            
        private:
        
            static std::list<shared*> all;
    };
    
    std::list<shared*> shared::all;
}

int main()
{
    for (int count = 0; count < 10; count++)
    {
        new test::shared();
    }
    
    std::cout << test::shared::getAll().size() << std::endl;
}