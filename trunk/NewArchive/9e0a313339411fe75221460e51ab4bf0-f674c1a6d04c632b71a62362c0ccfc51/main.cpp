#include <iostream>
#include <string>

int main()
{
    std::string word;
    while (std::cin >> word)
    {
        static std::string http = "http";
        auto start = word.find(http);
        if (start == std::string::npos)
        {
            continue;
        }
        
        if (word.size() > 100) word.resize(100); 
        
        auto end = std::min(word.find('"', start + http.size()),
                            word.find('\'', start + http.size()));
        if (end == std::string::npos)
        {
            continue;
        }
        
        std::cout << word.substr(start, end - start) << std::endl;
    }
}