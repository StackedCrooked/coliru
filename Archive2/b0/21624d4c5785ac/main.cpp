#include <iostream>
#include <string>
#include <vector>


template<typename unknownTemplateType>
void f(unknownTemplateType incomingT){
    std::cout << incomingT << '\n';
}
int main()
{
    f<double>(1);
    f<>('a');
    f(7);
    char a = 'b';
    char* b = &a;
    std::cout 
        << sizeof(a) 
        << " is the size of a! <3 \n" 
        << sizeof(b) << " is the size of pointer to a! <3 \n" 
        << std::endl;
}
