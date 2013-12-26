#include <fstream>
#include <iostream>
#include <string>

struct foo {
private:
    std::string text;
public:
    void populateText(std::ifstream & file) {
        std::getline(file, text);
    }
    friend std::ostream & operator<<(std::ostream &, foo);
};

std::ostream & operator<<(std::ostream & out, foo f) {
    return out << "foo: " << f.text;
}

int main() {
    std::ifstream file("main.cpp");
    foo f;
    f.populateText(file);
    std::cout << f << '\n';
}
