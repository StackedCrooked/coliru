#include <string>
#include <map>
#include <iostream>
#include <climits>

int main()
{
    std::map<std::string ,int > dup_counter;
    int linecount=0;

    std::cin >> linecount; //if this fails, count==0
    std::cin.ignore(); //consume the newline if any
    for(int i=0; i<linecount; ++i) 
    {
        std::string line;
        std::getline(std::cin, line);
        dup_counter[std::move(line)] += 1;
    }
    for(const auto& pair : dup_counter)
    {
        std::cout << pair.first << pair.second << '\n';
    }
}