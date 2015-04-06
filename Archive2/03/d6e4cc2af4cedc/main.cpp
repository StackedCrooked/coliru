#include <cstring>
#include <cstdio>
#include <iostream>
 
int main() 
{
    char str[20] = "Hello ";
    char str2[50] = "World!";
    cout<<strcat(str, str2);
    cout<<strcat(str, " hiWorld!");
    std::puts(str);
}