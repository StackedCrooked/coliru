#include <vector>

struct test
{
    enum class pica {};
    using dura = std::vector<pica>;
};

int main() {}
