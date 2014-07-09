#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <regex>

int main()
{
    std::string text("@TestTable[TestColumn], @TestTable[TestColumn2]");
    std::regex regex("\\w+\\[\\w+\\]");

    std::sregex_token_iterator iter(text.begin(), text.end(), regex, 0);
    std::sregex_token_iterator end;

    for( ; iter != end; ++iter ) {
        std::cout << *iter << std::endl;
    }
}