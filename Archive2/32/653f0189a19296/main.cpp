#include <iostream>
#include <vector>
#include <algorithm>

template <typename T, typename U>
void sortedInsert(std::vector<T>& vec, const U& value) {
    auto it = std::lower_bound(vec.begin(), vec.end(), value);
    vec.insert(it, std::move(T(value)));
}
    
int main() {

    std::vector<std::string> nomes;
    sortedInsert(nomes, "Pedro");
    sortedInsert(nomes, "Amanda");
    sortedInsert(nomes, "Maria");

    for (auto& nome : nomes)
        std::cout << nome << std::endl;
        
}