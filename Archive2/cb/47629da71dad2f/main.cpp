#include <iostream>
#include <unordered_map>

using UMap = std::unordered_map<int,int&>;

int main() {
    int a{1}, b{2}, c{3};
    UMap foo { {1,a},{2,b},{3,c} };

    // display b, use find as operator[] need DefaultConstructible
    std::cout << foo.find(2)->second << std::endl;
    
    // update b and show that the map really map on it
    b = 42;
    std::cout << foo.find(2)->second << std::endl;
    
    // copy is fine
    UMap bar = foo; // default construct of bar then operator= is fine too
    std::cout << bar.find(2)->second << std::endl;
}
