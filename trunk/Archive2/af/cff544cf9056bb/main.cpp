#include <functional>

namespace std {
template<typename T>
struct hash<typename std::enable_if<std::is_enum<T>::value, T>::type> : public std::hash<typename std::underlying_type<T>::type> {};
}

int main() {
    
}

