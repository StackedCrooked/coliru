#include <iostream>
#include <cstring>

using std::strlen;
using std::strcpy;

struct string
{
    char *buffer;
    std::size_t len;
    
    string() : buffer(nullptr), len(0)
    {}
    string(char const *str) : buffer(new char[strlen(str)]), len(strlen(str))
    {}
    string(string const& other) : buffer(other.data()), len(other.size())
    {}
    
    string& operator +=(string const& other)
    {
        std::size_t length = size() + other.size() + 1; // this->size() member
        char *temp = new char[length];                  // function and a +1 for the
        strcpy(temp, buffer);                           // null byte '\0'
        strcpy(temp, other.data());

        delete[] buffer;

        buffer = new char[length];
        strcpy(buffer, temp);     // copy temp into buffer
        
        return *this;
    }
    
    char *data() const { return buffer; }
    
    std::size_t size() const { return len; }
};

std::ostream& operator <<(std::ostream& os, string const& str)
{
    return os << str.data();
}

int main()
{
    string s1 = "Hello", s2 = " World";
    
    s1 += s2;
    
    std::cout << s1;
}