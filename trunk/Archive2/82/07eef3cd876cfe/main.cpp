#include <iostream>
#include <set>

int main() {
    
    std::set<std::string> nomes;
    nomes.insert("Pedro");
    nomes.insert("Amanda");
    nomes.insert("Maria");

    for (auto& nome : nomes)
        std::cout << nome << std::endl;
        
}