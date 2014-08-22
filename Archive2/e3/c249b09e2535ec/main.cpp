#include <iostream>
#include <string>
 
// declaration in namespace(file) scope
// (the definition is provided later)
int f1();
 
// simple function with a default argument, returning nothing
void f0(const std::string& arg = "world") {
    std::cout << "Hello, " << arg << '\n';
}
 
// function returning a pointer to f0
auto fp11() -> void(*)(const std::string&) {
    return f0;
}
 
// function returning a pointer to f0, pre-C++11 style
void (*fp03())(const std::string&) {
    return f0;
}
 
int main()
{
    f0();
    fp11()("test");
    fp03()("again");
    int f2(std::string) noexcept; // declaration in function scope
    std::cout << f2("bad12") << '\n';
}
 
// simple non-member function returning int
int f1() {
    return 42;
}
 
// function with an exception specification and a function try block
int f2(std::string str) noexcept try { 
    return std::stoi(str);
} catch(const std::exception& e) {
    std::cerr << "stoi() failed!\n";
    return 0;
}