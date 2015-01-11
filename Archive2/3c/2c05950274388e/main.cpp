#include <string>

int main() {
    char a[] = "a";
    const char* b = "b";
    std::string c = "c";
    static_assert(true != c, "c");
}