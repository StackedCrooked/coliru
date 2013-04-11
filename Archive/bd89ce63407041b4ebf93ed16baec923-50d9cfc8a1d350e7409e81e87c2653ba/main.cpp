#include <string>
#include <iostream>

size_t find_last(const std::string& str, const std::string& needle) {
    size_t last = std::string::npos;
    size_t next = 0;
    while((next = str.find(needle, next)) != std::string::npos) {
        last = next;
        next++;
    }
    return last;
}

int main() {
    std::string original = "asdfgsdfg:ijtbp ijdfgh ija::saf 1999 bp";

    size_t s = original.find(":");
    size_t e = find_last(original, "bp");
    std::string sub = original.substr(s + 1, e - s -1);
    std::cout << sub ;
}