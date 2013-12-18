#include <iostream>
#include <functional>
#include <map>

#define VK_UP 0x01
#define VK_DOWN 0x02

class Keyboard {
public:
    Keyboard() = default;
    void UpKey() {
        std::cout << "Call VK_UP" << std::endl;    
    }
    void DownKey() {
        std::cout << "Call VK_DOWN" << std::endl;    
    }
};

int main() {
    Keyboard keyboard;
    int testMessage = 0x01;
    
    //Keyboard mapping container
    std::multimap<int,std::function<void()>> keyMapping;
    
    //Add 2 key options + function calls
    keyMapping.emplace(VK_UP,[&](){ keyboard.UpKey(); });
    keyMapping.emplace(VK_DOWN,[&](){ keyboard.DownKey(); });
    
    //Iterate all functions to check which message it is
    for (const auto& e : keyMapping) {
        if (testMessage == e.first) {
            e.second();
            break;
        }
    }
}