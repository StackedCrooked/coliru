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
inline void _printWithLeadingSeparator(const SeparatorType& separator, T&& arg) {
    _print(separator);
    _print(std::forward<T>(arg));
}

template <typename SeparatorType, typename T, typename... Args>
inline void _printWithLeadingSeparator(const SeparatorType& separator, T&& arg, Args&&... args) {
    _printWithLeadingSeparator(separator, std::forward<T>(arg));
    _printWithLeadingSeparator(separator, std::forward<Args>(args)...);
}

template <typename SeparatorType, typename T, typename... Args>
inline void _printList(const SeparatorType& separator, T&& arg, Args&&... args) {
    // Prints first argument and then all successive arguments with leading separators
    _print(std::forward<T>(arg));
    _printWithLeadingSeparator(separator, std::forward<Args>(args)...);
}

// Public functions:
template<typename... Args>
void log(Args... args) {
    _print("LOG ");
    _printList(", ", args...);
    _printLine();
}

// Usage:
int main() {
    log(1, 2.5, 'a', "Hello", "World");
}