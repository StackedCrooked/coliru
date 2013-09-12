#include <string>

namespace evil {
    // I'm cheating with std::string to handle the deletion and shit.
    struct string : std::string {
        using std::string::string;
        
        string(string&& s)
        : std::string(std::move(s)) {
            s.has_garbage = true;
            s.garbage = &s[0];
        }
        char* garbage = nullptr;
        bool has_garbage = false;
    };
}