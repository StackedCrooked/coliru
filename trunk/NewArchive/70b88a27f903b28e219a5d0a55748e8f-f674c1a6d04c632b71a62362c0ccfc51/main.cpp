#include <iostream>
#include <string>

template<typename F>
void split(const std::string & text, const std::string & delim, F&& callback)
{
    std::string::size_type begin = 0;
    while (true)
    {
        std::string::size_type end = text.find(delim, begin);
        if (end == std::string::npos)
        {
            callback(text.substr(begin, std::string::npos));
            break;
        }

        callback(text.substr(begin, end - begin));
        begin = end + delim.size();
    }
}


int main()
{
    split("abc-123-def", "-", [](const std::string& part) {
        std::cout << "part: " << part << std::endl;
    });
}