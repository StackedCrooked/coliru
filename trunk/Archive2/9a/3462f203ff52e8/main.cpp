#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>

std::vector<std::pair<std::string, std::string>> users { 
    { "joe", "123"},
    { "jim", "qwerty"},
    { "john", "asdf"}
};

int main() { 
    std::string name, pw;
    
    std::cout << "Please enter name and password";
    std::cin >> name >> pw;
    
     if (std::find(users.begin(), users.end(), std::make_pair(name, pw)) != users.end())
         std::cout << "Welcome : " << name;
    else
        std::cout << "who are you?";
}

