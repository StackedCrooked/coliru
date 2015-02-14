#include <cstdint>
#include <array>
#include <limits>

// Counts the occurrences of each byte value.
struct Distribution
{
    void process(std::uint8_t* data, std::size_t size)
    {
        for (auto i = 0; i != size; ++i)
        {
            // this seems to be very prone to aliasing troubles
            mDistribution[data[i]]++;
        }
    }
    
    std::array<std::uint64_t, std::numeric_limits<std::uint8_t>::max()> mDistribution;
};


