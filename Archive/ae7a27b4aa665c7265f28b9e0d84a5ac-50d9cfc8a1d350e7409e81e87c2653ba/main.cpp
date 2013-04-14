#include <stdio.h>

#include <type_traits>

static_assert(std::is_void<void>(), "void is void");

int main() {
    perror("Error");
}
