#include <iostream>
#include <cstring> // :/

class my_string {
private:
    char* contents;
    unsigned len;
    unsigned capacity;
public:
    my_string(): contents(NULL), len(0), capacity(0) {}
    my_string(const char* str) {
        len = strlen(str);
        capacity = len + 1;
        contents = new char[capacity];
        for(unsigned i = 0; i < len; ++i)
            contents[i] = str[i];
    }
    my_string(const my_string& other): len(other.len), capacity(other.capacity) {
        delete[] contents;
        contents = new char[capacity];
        for(unsigned i = 0; i < len; ++i)
            contents[i] = other.contents[i];
    }
    my_string& operator=(const my_string& other) {
        delete[] contents;
        contents = new char[capacity];
        for(unsigned i = 0; i < len; ++i)
            contents[i] = other.contents[i];
        return *this;
    }
    ~my_string() {
        delete[] contents;
    }
    friend std::ostream& operator<<(std::ostream& out, const my_string& str) {
        return str.contents == NULL ? out : out << str.contents;
    }
};

int main() {
    my_string str = "Hello World";
    std::cout << str;
}