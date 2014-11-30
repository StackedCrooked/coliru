#include <iostream>
#include <string>

// Basic functions:
template <typename T>
inline void _print(T arg) {
    std::cout << arg;
}

inline void _printLine() {
    std::cout << std::endl;
}

// Functions for multiple arguments:
template <typename SeparatorType, typename T>
inline void _printWithLeadingSeparator(SeparatorType&& separator, T&& arg) {
    _print(std::forward<SeparatorType>(separator));
    _print(std::forward<T>(arg));
}

template <typename SeparatorType, typename T, typename... Args>
inline void _printWithLeadingSeparator(SeparatorType&& separator, T&& arg, Args&&... args) {
    _printWithLeadingSeparator(std::forward<SeparatorType>(separator), std::forward<T>(arg));
    _printWithLeadingSeparator(std::forward<SeparatorType>(separator), std::forward<Args>(args)...);
}

template <typename SeparatorType, typename T, typename... Args>
inline void _printList(SeparatorType&& separator, T&& arg, Args&&... args) {
    // Prints first argument and then all successive arguments with leading separators
    _print(std::forward<T>(arg));
    _printWithLeadingSeparator(std::forward<SeparatorType>(separator), std::forward<Args>(args)...);
}

// Public functions:
template<typename T>
void log(T&& arg) {
    _print("LOG ");
    _print(std::forward<T>(arg));
    _printLine();
}

template<typename... Args>
void log(Args&&... args) {
    _print("LOG ");
    _printList(", ", std::forward<Args>(args)...);
    _printLine();
}

// Usage:
int main() {
    log(1);
    log(3.1415926535, "Hello, world!");
    log("this", "supports", "four", "arguments");
}