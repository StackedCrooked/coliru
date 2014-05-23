#include <iostream>

template<typename O, typename T> O& operator%(O& o, const T&) {
    return o << "I don't know what it is\n";
}

template<typename O, std::size_t N> O& operator%(O& o, const char[N]) {
    return o << "const char[" << N << "], probably a string literal\n";
}

template<typename O> O& operator%(O& o, const char*) {
    return o << "const char*, probably a string literal\n";
}

template<typename O, std::size_t N> O& operator%(O& o, char[N]) {
    return o << "char[" << N << "]\n";
}

template<typename O> O& operator%(O& o, char*) {
    return o << "char*\n";
}

template<typename O> O& operator%(O& o, int) {
    return o << "int\n";
}

template<typename O> O& operator%(O& o, char) {
    return o << "char\n";
}

template<typename O> O& operator%(O& o, bool) {
    return o << "bool\n";
}

template<typename O> O& operator%(O& o, void*) {
    return o << "void*\n";
}

template<typename O> O& operator%(O& o, std::nullptr_t) {
    return o << "nullptr_t\n";
}

template<typename O> O& operator%(O& o, double*) {
    return o << "double*\n";
}

template<typename O> O& operator%(O& o, double) {
    return o << "double\n";
}





int main() {
    char a[2] = "a";
    double* p = nullptr;
    std::cout % a % "b" % 3 % true % 4.1 % '\0' % 0 % p % nullptr;
}

