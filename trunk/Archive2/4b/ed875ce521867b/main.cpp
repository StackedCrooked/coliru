#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char *str = "hello";

    while (*str) {
        cout << *str;
        *str++;
    }

    return 0;
}