#include <regex>
#include <iostream>

int main()
{
    std::string output = "summer1969 2014-03-07 Test.list.everything.1234 123.4.4.34 moreCode";
    std::cmatch result;
    std::regex rx ("(([a-zA-Z]+\\.{0,1})+)\\.[0-9]+");
    std::regex_search(output.c_str(), result, rx);
    for(int i = 0; i < result.size(); i++)
    {
        std::cout << i << ". " << result[i] << std::endl;
    }
    system("pause");
    return(0);
}