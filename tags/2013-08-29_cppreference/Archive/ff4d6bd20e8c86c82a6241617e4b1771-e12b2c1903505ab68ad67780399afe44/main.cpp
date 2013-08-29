#include <iostream>
#include <iomanip>
#include <limits>

#define NUMLIM(T, prop) do {\
        std::cout << std::setw(20) << #T \
                  << std::setw(20) << #prop ": " \
                  << std::numeric_limits<T>::prop << "\n"; \
    } while(0)

#define CONTRAST(prop) do {\
        NUMLIM(float, prop); \
        NUMLIM(double, prop); \
        NUMLIM(long double, prop); \
        std::cout << "\n"; \
    } while(0)

std::ostream& operator<<(std::ostream& os, std::float_round_style frs)
{
    switch(frs)
    {
        case std::round_indeterminate:       return os << "round_indeterminate";
        case std::round_toward_zero:         return os << "round_toward_zero";
        case std::round_to_nearest:          return os << "round_to_nearest";
        case std::round_toward_infinity:     return os << "round_toward_infinity";
        case std::round_toward_neg_infinity: return os << "round_toward_neg_infinity";
    }
}

int main()
{
    std::cout << std::boolalpha;
    CONTRAST(digits);
    CONTRAST(digits10);
    CONTRAST(max_digits10);
    CONTRAST(tinyness_before);
    CONTRAST(epsilon());
    CONTRAST(round_error());
    CONTRAST(denorm_min());
    CONTRAST(round_style);
}
