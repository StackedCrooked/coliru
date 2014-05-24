#include <limits>
#include <cstring>
#include <cstdint>

template <class TO, class FROM>
inline TO punning_cast(const FROM &input)
{
    TO out;
    std::memcpy(&out, &input, sizeof(TO));
    return out;
}

int main()
{
    uint32_t i = std::numeric_limits<uint32_t>::min();
    uint32_t count = 0;

    while (1)
    {
        if (i == std::numeric_limits<uint32_t>::max())
            break;
        float n = punning_cast<float>(i);
        if(n >= 0.0f && n <= 1.0f)
            count++;
        i++;
    }

    return count;
}