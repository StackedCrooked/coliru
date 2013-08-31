#include <iostream>
#include <string>

struct MyString : std::string {
    MyString & operator=(std::string const& rhs) {
        static_cast<std::string&>(*this) = rhs.c_str();
        return *this;
    }
};

int main() {
    MyString myStr;
    myStr = std::string("Hello, std::string!");
    std::cout << myStr << std::endl;
    return 0;
}