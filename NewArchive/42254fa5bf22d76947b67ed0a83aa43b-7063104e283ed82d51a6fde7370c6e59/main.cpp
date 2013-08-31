#include <iostream>
#include <string.h>
#include <typeinfo>

template <typename C, typename T=std::char_traits<C> >
class my_basic_stream : public std::basic_ostream<C, T>
{
};

typedef my_basic_stream<char> mystream;

mystream& operator<<(mystream& os, const char* msg)
{
    //writing directly to stream
    os.write(msg,strlen(msg));
    return os;
}


int main()
{
    mystream foo;
    foo.rdbuf(std::cout.rdbuf());
    std::cout << typeid(foo << "message1 " << "message2").name();
}
