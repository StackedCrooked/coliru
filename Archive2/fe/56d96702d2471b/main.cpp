#include <string>
#include <ios>
#include <type_traits>
 
// type alias, identical to
// typedef std::ios_base::fmtflags flags;
using flags = std::ios_base::fmtflags;
// the name 'flags' now denotes a type:
flags fl = std::ios_base::dec;
 
// type alias, identical to
// typedef void (*func)(int, int);
using func = void (*) (int,int);
// the name 'func' now denotes a pointer to function:
void example(int, int) {}
func fn = example;
 
// template type alias
template<class T> using ptr = T*; 
// the name 'ptr<T>' is now an alias for pointer to T
ptr<int> x;
 
// type alias used to hide a template parameter 
template <class CharT> using mystring = 
    std::basic_string<CharT,std::char_traits<CharT>>;
mystring<char> str;
 
// type alias can introduce a member typedef name
template<typename T>
struct Container {
    using value_type = T;
};

int main() 
{
    Container<int> c;
}