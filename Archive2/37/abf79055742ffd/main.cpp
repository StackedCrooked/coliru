#include <unordered_map>
#include <cstring>
#include <string>
#include <iostream>

struct Hash {
    std::size_t operator()(const char *x) const { return 0; }
    std::size_t operator()(const std::string& s) const { return 0; }
    typedef void is_transparent;
};

struct StringRef {
    StringRef(const std::string& s):x(&s[0]) { }
    StringRef(const char *s):x(s) { std::cout << "works: " << s << std::endl; }
    const char *x;    
};

struct Eq {
    bool operator()(StringRef a, StringRef b) const { 
        return std::strcmp(a.x, b.x) == 0; 
    }
    typedef void is_transparent;
};

int main() {
    std::unordered_map<std::string, std::string, Hash, Eq> um;
    um["haha"] = "lulz";
    std::cout << (um.find("haha") != um.end()) << std::endl;
    std::cout << (um.find("hmm") != um.end()) << std::endl;
}
