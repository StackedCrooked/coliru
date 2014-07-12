#include <iostream>
#include <string>

struct MyClass {
    std::string m_str = "OLD STRING";
};

void CopyString(MyClass& c, std::string x) {
    c.m_str = x;
}

int main() {
    MyClass c;
    CopyString(c, "NEW STRING");

    std::cout << c.m_str << std::endl;           // prints "OLD STRING"!!
}