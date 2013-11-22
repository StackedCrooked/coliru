#include <iostream>
#include <cstring>
 
int main()
{
    char input[] = "/home/user/hello.c";
    char* output = std::strrchr(input, '/');
    if(output)
        std::cout << output+1 << '\n';
}