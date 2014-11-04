#include <iostream>

void cm(const char (&h)[8]) 
    {std::cout << " const (&)[N] " << '\n';}
void cm(const char * h)
    {std::cout << " const char * " << '\n';}

int main()
{
    const char ccar[] = "errqweq";
    cm(ccar);
}