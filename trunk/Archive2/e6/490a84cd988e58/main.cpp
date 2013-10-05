#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

std::vector<std::string> parseData(const std::string& s)
{
    if (s.size() % 3 != 0) {
        throw std::runtime_error("incorrect data length");
    }

    std::vector<std::string> result;
    for (size_t i = 0; i <= s.size() - 3; i += 3) {
        result.emplace_back(s, i, 3);
    }
    
    return result;
}

int main()
{
    const std::string data = "G01G02G03G04G05";
    
    try {
        for (auto& elem : parseData(data)) {
            std::cout << elem << "\n";
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
    }
}