#include <iostream>


struct functions
{
    void (*f1)(void) ;
    void (*f2)(int) ;
};

void printone() {   std::cout << "one " ;}
void printtwo() {   std::cout << "two "; }

void printnum(int n) { std::cout << n; }

int main() {
    functions fncs;
    fncs.f1 = &printone;
    fncs.f2 = &printnum;
    
    fncs.f1(); fncs.f2(1);
    return 0;
}