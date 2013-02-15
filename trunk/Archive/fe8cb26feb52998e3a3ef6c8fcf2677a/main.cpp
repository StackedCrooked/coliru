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
    static void assign(T & out, T in)
    {
        out = std::tolower(in);
    }
};

typedef std::basic_string<char, lowercase_char_traits<char>> lowercase;

int main() 
{
    lowercase s1 = "Hello World";
    std::cout << s1.c_str() << std::endl;
    
    lowercase s2 = "HELLO WORLD";
    std::cout << std::boolalpha << (s1 == s2) << std::endl;
    
    lowercase s3 = "HELLO";
    s3 += " WorL";
    s3.append("D");
    std::cout << std::boolalpha << (s1 == s3) << std::endl;
    
    std::cout << s2.c_str() << std::endl;
    std::cout << s3.c_str() << std::endl;
}