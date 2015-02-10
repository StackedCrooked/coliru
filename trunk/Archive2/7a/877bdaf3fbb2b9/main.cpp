#include <cmath>

auto toBinary (auto number)
{
    auto result = 0;
    auto current = 0;
    while (number) {
        result += (number % 2) * pow(10, current);
        number /= 2;
        ++current;
    }
    return result;
}

int main() {}