#include <iostream>
#include <stdexcept>

template<class T>
int to_call(T arg) {
    std::cout << "Called with " << arg << "\n";
    return 0;
}

template<class T, class... Args>
int apply(int idx, const T& arg) {
    if (idx == 0) return to_call(arg);
    throw std::runtime_error("Not enough arguments.");
}

template<class T, class... Args>
int apply(int idx, const T& arg, Args... args) {
    if (idx == 0) return to_call(arg);
    return apply(--idx, args...);
}

int main(int argc, char** argv) {
    apply(1, "this", "that", "it");
    return 0;
}