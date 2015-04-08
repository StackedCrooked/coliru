#include <iostream>

typedef int miles;

namespace Jungle
{   
    template <typename T>
    class Tiger
    {
        public:
        void growl(T)
        {
            
        }
        
    };
}

int fly(miles distance)
{
   return distance + 10; 
}


int main()
{
   
   std::cout << "Hello World" << std::endl; 
   fly(10);
   return 0;
}