#include <iostream>
#include <string>
using namespace std;

void foo(const char* p) { }

template <int N>
void foo(const char (&p)[N]) = delete;

int main(int argc, char *argv[]) {
    char c[20] = "hello";
    foo(+c);
    foo(+"hello");
    return 0;
}