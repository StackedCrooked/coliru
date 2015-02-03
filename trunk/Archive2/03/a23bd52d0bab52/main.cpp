#include <iostream>
#include <fstream>
#include <string>

template<typename CharT, std::size_t MaxSize, typename Traits>
struct basic_string_thing
{
    CharT data[MaxSize+1];
};


//convenience "typedef
template<typename std::size_t MaxSize>
struct string_thing : public basic_string_thing<char, MaxSize, std::char_traits<char> >
{
    
};


template<typename T>
struct string_thing_trait;

template<typename CharT, std::size_t MaxSize, typename Traits>
struct string_thing_trait< basic_string_thing<CharT, MaxSize, Traits> >
{
    static const std::size_t max_size = MaxSize;
};

//uncomment to see that this specialization is necessary
/* 
template<std::size_t MaxSize>
struct string_thing_trait< string_thing<MaxSize> > 
{
    static const std::size_t max_size = MaxSize;
};
*/

int main()
{
    std::cout << string_thing_trait< string_thing<32> >::max_size << "\n";
}
