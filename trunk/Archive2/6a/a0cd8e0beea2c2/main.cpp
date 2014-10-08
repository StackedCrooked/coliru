#include <ctime>
#include <iostream>
 
int main()
{
    struct tm lex;
    std::asctime(&lex);
}