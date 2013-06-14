#include <iostream>
#include <string>

int main()
{
    std::string word;
    while (std::cin >> word)
    {
        static std::string http = "http";
        auto start = word.find(http);
        std::cout << "start: " << start;
        if (start == std::string::npos)
        {
            std::cout << std::endl;
            continue;
        }
        
        if (word.size() > 100) word.resize(100); // b
        
        std::cout << " => potential match: " << word;
        
        auto end = std::min(word.find('"', start + http.size()),
                            word.find('\'', start + http.size()));
        std::cout << " => end: " << end;
        if (end == std::string::npos)
        {
            std::cout << std::endl;
            continue;
        }
        
        std::cout << " -> " << word.substr(start, end - start) << std::endl;
    }
}