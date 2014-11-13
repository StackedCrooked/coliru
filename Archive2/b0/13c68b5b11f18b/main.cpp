#include <memory>
#include <algorithm>
#include <random>

static const constexpr std::size_t size = 1E7;

int main()
{
    std::unique_ptr<std::uint16_t[]> random_data( new std::uint16_t[size] );
    std::generate_n( random_data.get(), size, std::mt19937(std::random_device()()) );
}
