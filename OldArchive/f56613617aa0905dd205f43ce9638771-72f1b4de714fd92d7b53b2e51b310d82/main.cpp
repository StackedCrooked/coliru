#include <string>
#include <iostream>

enum class Colors{ RED, BLUE, GREEN };

struct myRedStruct{
    bool operator==(const Colors& c)const{
        if(c == Colors::RED)
            return true;
        return false;
    }
};

namespace ColorsUtils {
    using namespace std;
    
    template <typename ColorComparable>
    string to_string(const ColorComparable& c){
        if(c == Colors::RED)
            return "red";
        return "not red";
    }
    Colors from_string(string const&);
}

int main() {
    Colors c = Colors::BLUE;
    const auto& s = ColorsUtils::to_string(c);
    std::cout << s << std::endl;
    
    myRedStruct mrs;
    const auto & s2 = ColorsUtils::to_string(mrs);
    std::cout << s2 << std::endl;
}
