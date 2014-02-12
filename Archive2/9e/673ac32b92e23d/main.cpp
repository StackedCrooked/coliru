#include <iostream>
#include <map>
#include <functional>

void foo() {
    std::cout << " foo";
}
void bar() {
    std::cout << " bar";
}

int main() {
    std::map < int, std::function<void( )>> procedure_map;

	procedure_map = { { 1, foo }, { 3, bar }, };
    
    procedure_map[1]();
    procedure_map[3]();
}
