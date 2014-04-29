#include <stdio.h>
#include <string>
#include <cstring>
#include <unordered_map>

using namespace std;

int main(void) {

    // This works as expected
    unordered_map<std::string, int> m;
    m["foo"] = 42;
    printf("%i\n", m["foo"]);

    // This this doesn't compile
    unordered_map<std::string, std::string> m1;
    m1["foo"] = string("42");
    printf("%s\n", m1["foo"]);

    return 0;
}