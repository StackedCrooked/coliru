// http://stackoverflow.com/questions/28595531/overloading-enum-boolean-comparison
#include <iostream>

enum class TraceLevel : uint32_t {

    // Basic logging levels (may be combined with trace level)
    All = 0xFFFFFFFF,
    None = 0x00000000,
    Info = 0x00000001,
    Warning = 0x00000002,
    Error = 0x00000004,
    Logging = 0x0000000F,
};

//inline bool TraceLevel() { return static_cast<bool>(x); }

inline constexpr TraceLevel
operator&(TraceLevel __x, TraceLevel __y) {
    return static_cast<TraceLevel>
        (static_cast<uint32_t>(__x) & static_cast<uint32_t>(__y));
}

inline bool operator&&(TraceLevel __x, TraceLevel __y) {
    return static_cast<uint32_t>(__x & __y) > 0;
}

int main() {
    
    TraceLevel a = TraceLevel::Info;
    TraceLevel b = TraceLevel::Warning;

    TraceLevel c = a & b;

    if( a && b) {
        std::cerr << "a && b is true\n";
    } else {
        std::cerr << "a && b is false\n";
    }
}