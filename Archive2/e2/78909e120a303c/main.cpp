#include <iostream>
#include <string>
using namespace std;

void foo(const char* p) {
}

int main(int argc, char *argv[]) {
    char c[20] = "hello";
    foo(+c);
    foo(+"hello");
    return 0;
}