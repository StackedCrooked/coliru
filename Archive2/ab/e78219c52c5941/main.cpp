#include <string>

void foo(char *);

int main() {
    std::string s;
    foo(s.c_str());
}