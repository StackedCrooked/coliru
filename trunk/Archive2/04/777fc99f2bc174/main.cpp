#include <iostream>

void func(const char *p) { std::cout << p << "\n"; }
void func(std::nullptr_t p) { std::cout << "<null>\n"; }

int main()
{
    func("test");
    char *p=nullptr;
//    func(p);
    func(nullptr);
    return 0;
}