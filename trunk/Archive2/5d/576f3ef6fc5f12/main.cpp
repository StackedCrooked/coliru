#include <string.h>  //strncpy
#include <string>    //std::string
#include <iostream>  //std::cout

void copy (char dst[20], const std::string& src)
{
    strncpy (dst, src.c_str(), sizeof(dst)-1);
    dst[sizeof(dst)-1] = 0;
}

int main()
{
    const std::string src("content");
    char              dst[20];
    copy (dst, src);
    std::cout << dst << std::endl;
}
