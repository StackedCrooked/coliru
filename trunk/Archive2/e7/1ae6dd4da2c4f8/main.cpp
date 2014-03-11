#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

struct mychar
{
    mychar() = default;
    mychar(char const c)
        : ch(c)
    { }
    
    operator char() const
    { return ch; }
    
    char ch;
};

int main()
{
    std::basic_string<mychar> ms;
    ms.resize(4);
    ms[0] = {'b'}; ms[1] = {'o'}; ms[2] = {'o'}; ms[3] = {'b'}; 
    
    std::basic_stringstream<mychar> mss{ ms };
    
    /* How can I make this work? */
    std::copy(std::istream_iterator<mychar, mychar>(mss),
              std::istream_iterator<mychar, mychar>(),
              std::ostream_iterator<mychar>(std::cout));
    std::for_each(std::istream_iterator<char, mychar>(mss),
                  std::istream_iterator<char, mychar>(),
                  [](char const &mc){ std::cout << mc; });
    std::cout << std::endl;
}
