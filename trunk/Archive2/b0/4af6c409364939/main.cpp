#include <iostream>
#include <vector>
#include <algorithm>

void sortedInsert(std::vector<std::string>& vec, std::string value) {
    auto it = std::lower_bound(vec.begin(), vec.end(), value);
    vec.insert(it, std::move(value));
}
    
int main() {

    std::vector<std::string> nomes;
    sortedInsert(nomes, "Pedro");
    sortedInsert(nomes, "Amanda");
    sortedInsert(nomes, "Maria");

    for (auto& nome : nomes)
        std::cout << nome << std::endl;
        
}