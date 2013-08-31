#define CPPBEGININCLUSION R"(
#define CPPENDINCLUSION )"
#include <cstdio>

int main() {
    std::puts(CPPBEGININCLUSION ## meh ## CPPENDINCLUSION);
}
