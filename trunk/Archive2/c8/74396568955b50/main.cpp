#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main() {
    string s = "[self hello];";
    string x1 = R"raw(\[(\w+)\s+(\w+)\]\;)raw";
    regex re(x1);
    
    sregex_token_iterator it(s.begin(),s.end(),re,-1);
    sregex_token_iterator reg_end;
    for (; it != reg_end; ++it)
    {
        auto a = *it;
        std::cout << a;
    }
}