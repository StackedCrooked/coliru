#include <cmath>
#include <cstdio>

int main() {
    std::printf("%s", std::isnan(std::sqrt(-1)) ? "true" : "false");
}