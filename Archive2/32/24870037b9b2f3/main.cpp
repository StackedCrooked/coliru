#include <iostream>
#include <string>
 
struct Foo {
    static int foo_xalloc;
    std::string data; 
    Foo(const std::string& s) : data(s) {}
};
 
// allocates the iword storage for use with Foo objects
int Foo::foo_xalloc = std::ios_base::xalloc();
 
// This user-defined operator<< prints the string in reverse if the iword holds 1
std::ostream& operator<<(std::ostream& os, Foo& f)
{
    if(os.iword(Foo::foo_xalloc) == 1)
        return os << std::string(f.data.rbegin(), f.data.rend());
    else
        return os << f.data;
}
 
// This I/O manipulator flips the number stored in iword between 0 and 1
std::ios_base& rev(std::ios_base& os)
{
    os.iword(Foo::foo_xalloc) = !os.iword(Foo::foo_xalloc);
    return os;
}
 
int main()
{
    Foo f("example");
    std::cout << f << '\n' << rev << f << '\n' << rev << f << '\n';
}