#include <iostream>
#include <string>

int main() {
    std::string text("StringOfLength16");
    
    std::cout << text.rfind("") << " " << text.size() << std::endl;
}