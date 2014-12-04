#include <iostream>
#include <string>

template <class T1, class T2>
inline void construct(T1* p, const T2& value) {
    new (p) T1(value);
}

int main(){
    std::string* myString = new std::string;
    construct(myString, "Hello World");
    std::cout << *myString << std::endl;
    return 0;
}