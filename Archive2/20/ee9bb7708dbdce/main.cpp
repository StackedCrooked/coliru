#include <iostream>
#include <iostream>
#include <map>

int main() {
    std::map<std::string, std::map<std::string, float>>  _ScalingMapVolume = 
    { 
        { "AA", {
            { "busy_timeout", 1.0f }
        } }, 
        { "BB", {
            { "cache_size", 2.0f }
        } } 
    };
    std::cout << _ScalingMapVolume["AA"]["busy_timeout"] << std::endl;
}