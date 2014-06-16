#include <iostream>
#include <map>
#include <string>
#include <functional>

void hello() {
    std::cout << "used as a greeting or to begin a telephone conversation.";
}

int main (int argc, char ** argv) {
    std::map<std::string, std::function<void()>> map;
    map["hello"] = hello;
    
    std::string str;
    std::cin >> str;
    if (map.find(str) == map.end()) {
        std::cout << "couldn't find function";
    } else {
        map[str]();
    }
}