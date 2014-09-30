#include <boost/timer/timer.hpp>
#include <boost/locale.hpp>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    {
        int i = 100000;
        string str;
        boost::timer::auto_cpu_timer t;        
        while(i--) {
            str = "test string";
        }
        std::cout << "string from const char" << std::endl;
        std::cout << "result: " << str << std::endl;
    }
    {
        int i = 100000;
        wstring str;
        boost::timer::auto_cpu_timer t;        
        while(i--) {
            str = boost::locale::conv::utf_to_utf<wstring::value_type>("test string");
        }
        std::cout << "wstring from const char" << std::endl;
        std::wcout << "result: " << str << std::endl;        
    }    
    
    return 0;
}