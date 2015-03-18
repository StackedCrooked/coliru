#include <iostream>
#include <list>
#include <string>
#include <locale>
#include <sstream>

int main(int argc, char **argv)
{
    std::list <std::string> c1;

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
    std::advance(en, RandNum);

    std::wstringstream ws;
    ws << en->c_str();
    std::wstring s2 = ws.str();
    
    std::wcout << s2;
}