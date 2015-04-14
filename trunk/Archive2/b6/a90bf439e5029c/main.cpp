#include <iostream>
#include <string>
 
int main()
{
    // the test string
    std::string str = std::string("https://www.google.com:80/search/some/path");
 
    std::string::size_type pos = str.find_first_of(':');
    std::cout << ": " << pos << '\n';
    std::string scheme = str.substr(0, pos);
    std::cout << "scheme: " << scheme << "\n";
    std::string schemeDelim = str.substr(pos, 3);
    std::cout << "Delim " << schemeDelim << "\n";
    pos += 3;
    std::string::size_type next = str.find_first_of('/', pos);
    std::cout << "/ " << next << '\n';
    std::string host = str.substr(pos, next - pos);
    std::cout << "host " << host << '\n';
    pos = next + 1;
    next = str.find_first_of('?', pos);
    std::cout << "/ " << next << '\n';
    std::string path = str.substr(pos, next - pos);
    std::cout << "path " << path << '\n';
}