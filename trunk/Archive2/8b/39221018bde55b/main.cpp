#include <iostream>
#include <string>
#include <vector>
#include <boost/locale.hpp>
#include <boost/spirit/include/qi.hpp>

int main()
{
    namespace qi =boost::spirit::qi;
   
    std::string in = u8"Привет";
    std::wstring strout;
    std::wstring strin = boost::locale::conv::utf_to_utf<wchar_t>(in);
    qi::parse(strin .begin(), strin .end(), qi::raw[*qi::standard_wide::char_], strout);
    std::cout << boost::locale::conv::utf_to_utf<char>(strout);

}
