#include <iostream>
#include <string>

template<typename T>
struct lowercase_char_traits : std::char_traits<T>
{
    static T* copy(T* dest, const T* src, std::size_t count )
    {
         for(size_t i = 0 ; i < count ; ++i)
              dest[i] = std::tolower(src[i]);
         return dest;
    }
};

typedef std::basic_string<char, lowercase_char_traits<char>> lowercase;

int main() 
{
    lowercase s1 = "Hello World";
    std::cout << s1.c_str() << std::endl;
    
    lowercase s2 = "HELLO WORLD";
    std::cout << std::boolalpha << (s1 == s2) << std::endl;
}