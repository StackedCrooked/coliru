#include <iostream>


void test(char c)
{
    std::cout << "char\n";
}

void test(signed char c)
{
    std::cout << "signed char\n";
}

void test(unsigned char c)
{
    std::cout << "unsigned char\n";
}


int main(int argc, char **argv){
    
    char a;
    signed char b;
    unsigned char c;
    test(a);
    test(b);
    test(c);
    

    return 0;
}