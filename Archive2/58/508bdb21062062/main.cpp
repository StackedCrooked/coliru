#include <stdio.h>

template<class T>
int to_call(T arg) {
    printf("%s", arg); // might
    return 0;
}

template<class T, class... Args>
int apply(int idx, const T& arg) {
    if (idx == 0) return to_call(arg);
    throw 1;
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