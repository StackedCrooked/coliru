#include <list>
#include <iostream>

namespace test
{
    class shared;
    
    class platform
    {
        public:
            
            platform()
            {
                allList.push_back(this);
            }
            
            ~platform()
            {
                allList.remove(this);
            }
            
            virtual void open()
            {
                std::cout << "platform open called" << std::endl;
            }
            
            virtual void close()
            {
                std::cout << "platform close called" << std::endl;
            }
            
            void setSomething(int something) const
            {
                std::cout << "set something to " << something << std::endl;
                std::cout << "btw getAll size is " << getAll().size() << std::endl;
            }
            
            static const std::list<platform*>& getAll()
            {
                return allList;
            }
            
        private:
        
            static std::list<platform*> allList;
    };
    
    std::list<platform*> platform::allList;
    
    class shared : platform
    {
        public:
            
            shared()
            {
                setSomething(666);
                
                allList.push_back(this);
            }
            
            ~shared()
            {
                allList.remove(this);
            }
            
            virtual void open() override final
            {
                std::cout << "shared open called" << std::endl;
                
                platform::open();
                
                openList.push_back(this);
            }
            
            virtual void close() override final
            {
                std::cout << "shared close called" << std::endl;
                
                platform::close();
                
                openList.remove(this);
            }
            
            static const std::list<shared*>& getAll()
            {
                return allList;
            }
            
            static const std::list<shared*>& getOpen()
            {
                return openList;
            }
            
        private:
        
            static std::list<shared*> allList;
            static std::list<shared*> openList;
    };
    
    std::list<shared*> shared::allList;
    std::list<shared*> shared::openList;
}

int main()
{
    for (int count = 0; count < 10; count++)
    {
        auto yay = new test::shared();
        
        yay->open();
    }
    
    std::cout << test::shared::getAll().size() << std::endl;
}