#include <iostream>
#include <string>


struct MyString : public std::string {
    using std::string::string;
};

int main()
{
    MyString stg {"Thomas Haune!"};
    std::cout << stg;
}
