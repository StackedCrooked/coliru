#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <map> 
#include <functional>

class Shibe {
    public:
        template <typename ReturnType = int, typename... Args>
        Shibe(Args... args) {
            std::function<ReturnType(args...)> f;
            
        }
};

int main()
{
    std::map<std::string, Shibe> cmds;
}