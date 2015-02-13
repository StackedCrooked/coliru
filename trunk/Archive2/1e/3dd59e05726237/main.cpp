#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

struct User
{
    std::string name;
    std::string password;
    
    bool operator==(const User& other)
    {
        return name == other.name && password == other.password;
    }
};

int main()
{
    std::vector<User> users = { { "foo", "bar" }, { "baz", "foo" } };
    
    User me = { "foo", "bar" };
    if (std::find(users.begin(), users.end(), me) != users.end())
        std::cout << "Password correct" << std::endl;
    else
        std::cout << "GTFO" << std::endl;
        
    return 0;
}