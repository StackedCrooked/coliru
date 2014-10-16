#include <iostream>

char caa[] = "ЛيЛيЛي";
char *a = caa;

void foo(char t[])
{
    std::cout << sizeof(t);
}
int main()
{
    std::cout << sizeof(caa) << std::endl;
    foo(caa);
}

