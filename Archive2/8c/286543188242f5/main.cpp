#include <string>

struct MyString : std::string
{
    using std::string::string;
};

int main()
{
    std::string h = "Hello";
    
    MyString x(h); // Y U NO WORK
}