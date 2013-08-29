#include <cstdio>

void blah(char const*)  { printf("const char*\n"); }

template<class T, std::size_t N>
void blah(T (&)[N])     { printf("T (&)[N]\n"); }

int main() {
    char a[4];
    blah(a);
    blah(&a[0]);
}