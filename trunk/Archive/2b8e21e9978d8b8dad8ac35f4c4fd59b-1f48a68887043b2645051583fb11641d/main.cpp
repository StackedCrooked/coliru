#include <string>
#include <iostream>
#include <stack>

bool parenMatch(const std::string& str) {
    int parenCount = 0;
    for(auto& i : str) {
        if(i == '(' || i == '<' || i == '[')
            ++parenCount;
        if(i == ')' || i == '>' || i == ']')
            --parenCount;
    }
    return parenCount == 0;
}

int main() {
    std::cout << std::boolalpha 
              << parenMatch("(()))") << ' ' 
              << parenMatch("(((((((((((((((()()()()()))))()()))))))))") << ' '
              << parenMatch("(((((((((((((((((((((())))))))))))))))))))))");
}