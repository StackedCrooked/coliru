#include <stdio.h>
#include <string.h>

auto f(const char* s, size_t n) {
    printf("char* size_t %u\n", (unsigned)n);
    (void)s;
}
auto f(const char* s) {
    printf("char*\n");
    return f(s, strlen(s));
}
template<size_t N> inline auto
f( const char (& s)[N] ) {
    printf("char[&u]\n");
    return f(s, N-1);
}

int main() {
    char buffer[] = "Hello World";
    f(buffer);
    f(+buffer);
    buffer[5] = 0;
    f(buffer);
    f(+buffer);
}