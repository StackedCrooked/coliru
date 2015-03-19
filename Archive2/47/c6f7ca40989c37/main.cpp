#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <stdexcept>
 
void checked_sscanf(int count, const char* buf, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    if(std::vsscanf(buf, fmt, ap) != count)
        throw std::runtime_error("parsing error");
    va_end(ap);
}
 
int main()
{
    try {
        int n, m;
        std::cout << "Parsing '1 2'...";
        checked_sscanf(2, "1 2", "%d %d", &n, &m);
        std::cout << "success\n";
        std::cout << "Parsing '1 a'...";
        checked_sscanf(2, "1 a", "%d %d", &n, &m);
        std::cout << "success\n";
    } catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}