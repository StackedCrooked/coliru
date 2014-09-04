#include <cstddef>
#include <cstdio>
#include <limits>
#include <random>

int main()
{
    std::mt19937 rng;

    std::seed_seq sequence{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    rng.seed(sequence);
    rng.discard(12 * 629143);

    for (std::size_t i = 0; i != 12; ++i)
    {
        float random = std::generate_canonical<float,
            std::numeric_limits<float>::digits>(rng);

        if (random == 1.0f)
        {
            std::printf("--> %a\n", static_cast <double> (random));
        }
        else
        {
            std::printf("%e\n", random);
        }
    }

    return 0;
}