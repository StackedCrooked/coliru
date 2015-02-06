#include <sstream>
#include <iostream>
 
void print_stringbuf(std::streambuf* p)
{
    std::istream buf(p); // buf shares the buffer with s1
    int n;
    buf >> n;
    std::cout << n;
} // calls the destructor of buf. p remains unaffected
 
int main()
{
    std::istringstream s1("10 20");
    print_stringbuf(s1.rdbuf());
    int n;
    s1 >> n;
    std::cout << ',' << n << '\n';
}