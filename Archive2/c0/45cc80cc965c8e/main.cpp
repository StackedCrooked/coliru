#include <string>
#include <algorithm>
#include <iostream>

std::string nameFromPathname(std::string pathname, char separator = '/')
{
    std::string::reverse_iterator lastSep = std::find(
                pathname.rbegin(), pathname.rend(), separator);
    return std::string(lastSep.base(), pathname.end());
}

void test(std::string const& s)
{
    std::cout << s << ": " << nameFromPathname(s) << std::endl;
}

int main()
{
    test("file.txt");
    test("/file.txt");
    test("./file.txt");
    test("/home/doug/file.txt");
    return 0;
}
