#include <iostream>

/// Clamps value to be >= minimum and <= maximum.
template <typename T>
constexpr T clamp(T value, T minimum, T maximum)
{
	return value < minimum ? minimum : (value > maximum ? maximum : value);
}

struct CustomType
{
    double value;
    constexpr CustomType(const double value): value(value) {}
    bool operator<(const CustomType& other) const { return value < other.value; } // Not constexpr.
    bool operator>(const CustomType& other) const { return value > other.value; } // Not constexpr.
};

int main()
{
    constexpr double x = clamp(-1.0, 0.0, 1.0);
    constexpr CustomType y = clamp(CustomType(2.0), CustomType(0.0), CustomType(1.0));
    std::cout << x << ", " << y.value << std::endl;
}
