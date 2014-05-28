#include <limits>

int main()
{
    static_assert(std::numeric_limits<short>::max() <= std::numeric_limits<unsigned>::max(), "bummer");
}
