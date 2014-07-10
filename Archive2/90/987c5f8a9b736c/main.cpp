#include <iostream>
#include <string>
namespace first { void f() { std::cout << "Hello"; } }
struct second { static void f() { std::cout << ", "; } }
struct third_ty { void f() { std::cout << "World!"; } }
third_ty third;