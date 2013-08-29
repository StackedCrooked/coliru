#include <iostream>
#include <fstream>      // std::filebuf
#include <string.h>

template <typename C, typename T=std::char_traits<C> >
class my_basic_stream : public std::basic_ostream<C, T>
{
};

typedef my_basic_stream<char> mystream;

mystream& operator<<(mystream& os, const char* msg)
{
    //using ostream << operator
    dynamic_cast<std::ostream&>(os) << msg << std::endl;
    //writing directly to stream
    os.write(msg,strlen(msg));
    return os;
}


int main()
{
    mystream foo;
    foo.rdbuf(std::cout.rdbuf());
    foo << "message1" << "message2";
}
