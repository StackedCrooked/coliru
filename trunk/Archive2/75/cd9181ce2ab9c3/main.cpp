#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> clauses{
        "1 2 0",
        "1 2 3 0",
        "1 0",
        "3 4 0",
    };
    
    clauses.erase(
        std::remove_if(
            clauses.begin(), clauses.end(), [](const std::string &s) {
                return s.find('1') != std::string::npos;
            } 
        ), 
        clauses.end()
    );
    
    for (const auto &clause : clauses) {
        std::cout << clause << '\n';
    }
}