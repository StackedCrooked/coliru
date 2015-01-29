#include <iostream>
#include <string>
#include <regex>
 
std::string csz_ipv4 = "(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)";
 
int main()
{
    std::string fnames[] = {"foo.txt", "bar.txt", "192.168.64.58", "zoidberg"};
    
    std::regex ip_regex( csz_ipv4 );
 
    for (const auto &fname : fnames)
    {
        if( std::regex_match( fname, ip_regex ) )
        {
            std::cout << fname << '\n';
        }
    }   
}