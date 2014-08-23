
template<class First>
bool equal_to_any(const First& first) 
{return false;}
template<class First, class Second, typename... Rest>
bool equal_to_any(const First& first, const Second& second, const Rest&...rest) 
{return first==second || equal_to_any(first, rest...);}


#include <string>
std::string MyCurrentFolder() {return {};}

int main() {
    std::string MyStr;
    if (equal_to_any(MyStr, MyCurrentFolder() + "test",
                            MyCurrentFolder() + "test,",
                            MyCurrentFolder() + "test, ",
                            "test",
                            "test,",
                            "test, "))
    {
        throw 1;
    }
}