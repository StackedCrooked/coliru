#include <string>
#include <iostream>

enum class Colors{ RED, BLUE, GREEN };

namespace ColorsUtils {
    using namespace std;
    string to_string(Colors){
        return "randomColor";
    }
    Colors from_string(string const&);
}

int main() {
    Colors c = Colors::RED;
    const auto& s = ColorsUtils::to_string(c);
    std::cout << s << std::endl;
}
