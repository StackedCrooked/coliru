#include <iostream>
#include <vector>
#include <map>

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
template class Jungle::Tiger<std::basic_string<char, std::char_traits<int>, std::allocator<float> > >;
template class Jungle::Tiger<std::basic_string<char*, std::char_traits<char*>, std::allocator<char*> > >;
template class Jungle::Tiger<std::basic_string<float, std::char_traits<float>, std::allocator<float> > >;
template class Jungle::Tiger<std::basic_string<int> >;

//template class Jungle::Tiger<std::basic_string<char> >;

template class Jungle::Tiger<std::wstring>;
template class Jungle::Tiger<std::u32string>;

template class Jungle::Tiger<std::map<int,int>>;
template class Jungle::Tiger<std::map<std::vector<int>,int>>;

//two situations if you write:
// 1) template class Jungle::Tiger<std::string>;
// or
// 2) template class Jungle::Tiger<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >;
// it will maintain the sugar of 1 and add sugar to 2 to become like 1... all other instanciations seem to work the same between clang and gcc

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