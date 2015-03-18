#include <iostream>
#include <list>
#include <string>
#include <locale>
#include <codecvt>
using namespace std;

int main(int argc, char **argv)
{
    list <string> c1;

    //Insert Data
    c1.push_back("one");
    c1.push_back("two");
    c1.push_back("three");
    c1.push_back("Four");
    c1.push_back("Five");
    c1.push_back("Six");
    c1.push_back("Seven");
    c1.push_back("Eight");
    c1.push_back("Nine");
    c1.push_back("Ten");




    //Random data from list

    int RandNum = 0 + (std::rand() % 10);

    auto en = c1.begin();
    advance(en, RandNum);


    typedef std::codecvt_utf8<wchar_t> convert_type;
    std::wstring_convert<convert_type, wchar_t> converter;
    std::wstring converted_str = converter.from_bytes(*en);
    
    std::wcout << converted_str;
}