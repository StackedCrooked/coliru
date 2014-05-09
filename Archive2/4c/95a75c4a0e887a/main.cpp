#include <string>
#include <map>
#include <iostream>
#include <climits>

int main()
{
    std::map<std::string ,int > linecounts;
    int count=0;

    std::cin >> count; //if this fails, count==0
    std::cin.ignore(); //consume the newline if any
    for(int i=0; i<count; ++i) 
    {
        std::string line;
        std::getline(std::cin, line);
        linecounts[std::move(line)] += 1;
    }
    for(const auto& pair : linecounts)
    {
        std::cout << pair.first << pair.second << '\n';
    }
}