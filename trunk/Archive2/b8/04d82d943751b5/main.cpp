#include <list>
#include <iostream>
#include <string>
#include <algorithm>
int main()
{
    std::list<std::string> temp;
    temp.push_back("huang");
    temp.push_back("ok");
    std::for_each(temp.begin(),temp.end(),[](const auto &value){
        std::cout << value << std::endl;
    });
    return 0;
}