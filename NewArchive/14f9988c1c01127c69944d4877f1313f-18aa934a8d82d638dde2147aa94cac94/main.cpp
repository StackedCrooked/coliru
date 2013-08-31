#include <iostream>

template<class T>
void f(T&&);

void f(char const*){std::cout << "const char*\n";}
void f(char*){std::cout << "char*\n";}

int main(){
    char buffer[] = "hi";
    f(buffer);
}