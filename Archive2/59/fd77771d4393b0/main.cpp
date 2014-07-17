#include <iostream>
#include <map>
#include <string>


struct Exception
{
    Exception& addTag(const std::string& name, const std::string& value)
    {
        tags[name] = value;
        return *this;
    }
    std::map<std::string, std::string> tags;
};



int main()
{
    try
    {
        throw Exception()
            .addTag("a", "1")
            .addTag("b", "2")
            .addTag("c", "3");  // potential life-time issue for original Exception object? 
    }
    catch (Exception& e)
    {
        for (auto&& tag : e.tags)
        {
            std::cout << tag.first << '=' << tag.second << ' ' ;
        }
    }
}