#include <iostream>
#include <string>

template <typename STRING>
struct outer
{
    struct inner
    {
        inner ():_string_ref (get_string()){}
        std::string const  &_string_ref; 
    };  

    static std::string const & get_string();
    static std::string _string;
    static inner   _bar;

};  

template <typename STRING>
std::string outer<STRING>::_string;


template <typename STRING>
typename outer<STRING>::inner outer<STRING>::_bar;


template <typename STRING>
std::string const &
outer<STRING>::get_string()
{
    _string = "bla";
    return _string;
}
//template std::string outer<std::string>::_string;
int main()
{

   const std::string &some =  outer<std::string>::_bar._string_ref;
   std::cout << "the value is " << outer<std::string>::_string << std::endl;

}