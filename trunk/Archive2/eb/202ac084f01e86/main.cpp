#include <sstream>
#include <iostream>
#include <stdexcept>

struct critical_error : std::runtime_error {
    critical_error(const std::string& s): std::runtime_error("critical error: " + s) {}
};

template<typename... Args>
void critical(Args&&... args) {
    std::ostringstream ss;
    using swallow = char[];
    (void)swallow{((ss << std::forward<Args>(args)), '\0')...};
    throw critical_error(ss.str());
}

int main() {
    critical(10, 11, "whoa", 1.4f);
}
    

