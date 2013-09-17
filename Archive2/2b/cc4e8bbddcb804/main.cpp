#include <map>
#include <iostream>


std::map<std::string,int> foo2() {
     std::map<std::string, int> word2idx;
     std::cout << "foo2 after init: " << &word2idx << std::endl;
     return word2idx;
}

void foo() {
    static std::map<std::string, int> word2idx;
    std::cout << "foo post init: " << &word2idx << std::endl;
    char * data = new char[100];
    delete[] data;
    word2idx = foo2();
    std::cout << "foo after foo2(): " << &word2idx << std::endl;
}

int main() {
    foo();
    foo();
 
    return 0;
}