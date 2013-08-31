#include <iostream>
#include <vector>
using namespace std;
template<typename Ret, typename... Args, typename... Rest>
void foo(Ret(*)(Args...), Rest...) {cout << "Scoped";}

int main() {
    char(*bar)(int, double) = nullptr;
    foo(bar, true, "hi");
}