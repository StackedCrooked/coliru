#include <string>
#include <iostream>

struct expression_template {
    const char* value;
};
struct result {
    std::string value;
    result(expression_template t) : value(t.value) {}
};
expression_template math(const char* value) {return  {value};}

int main() {
    auto res = math(std::string("HI").c_str());
    std::cout << res.value; //expression contains pointer to destroyed data, undefined behavior
    std::cout << res.value;
    std::cout << res.value;
    std::cout << res.value;
    std::cout << res.value;
    std::cout << res.value; //expression was also calculated six unneeded times!
}