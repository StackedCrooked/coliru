#include <iostream>
#include <vector>

typedef int miles;
typedef std::basic_string<char16_t> what;

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

template class Jungle::Tiger<std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t> > >;
template class Jungle::Tiger<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >;
template class Jungle::Tiger<std::wstring>;
template class Jungle::Tiger<std::u32string>;

template class Jungle::Tiger<std::vector<int>>;

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