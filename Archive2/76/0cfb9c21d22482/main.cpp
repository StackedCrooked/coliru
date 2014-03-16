#include <iostream>
#include <string>

template <typename T>
auto ReadLine(T& reader, std::string& line) -> decltype(reader.ReadString(line)) {
     return reader.ReadString(line); 
}

template <typename T>
auto ReadLine(T& reader, std::string& line) -> decltype(reader.ReadLine(line)) {
     return reader.ReadLine(line); 
}

struct foo {
    bool ReadString(std::string& s) { s = "foo"; return true; }
};

struct bar {
    bool ReadLine(std::string& s) { s = "bar"; return true; }
};

template <typename T>
void test_one(const char* name) {
    T t;
    std::string s;
    std::cout << "ReadLine(" << name << ")";
    if (ReadLine(t, s)) {
        std::cout << " = " << s;
    } else {
        std::cout << " fails";
    }
    std::cout << '\n';
}

int main() {
    test_one<foo>("foo");
    test_one<bar>("bar");
}
