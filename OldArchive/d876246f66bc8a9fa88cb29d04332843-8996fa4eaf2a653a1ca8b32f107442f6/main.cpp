#include <iostream>
#include <map>
#include <string>
#include <functional>

struct tokenList {};

std::map<std::string, std::function<std::string (const tokenList& tokens)>> evaluateOperator;

int main()
{
    evaluateOperator["="] = [](const tokenList& tokens) -> std::string
    {
        std::string temp("");
        
        return temp;
    };
}