#include <type_traits>
#include <utility>


struct padded
{
    unsigned u;
    char c;
};

static_assert(std::is_pod<padded>::value, "This is not a POD!");
static_assert(sizeof(padded) == sizeof(unsigned) + sizeof(char), "Size is not correct!");

int main() { }
