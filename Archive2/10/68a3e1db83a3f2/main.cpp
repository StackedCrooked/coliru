#include <iostream>
#include <string>
namespace first { void f() { std::cout << "Hello"; } }
struct second { static void f() { std::cout << ", "; } }
struct third { void f() { std::cout << "World!"; } }