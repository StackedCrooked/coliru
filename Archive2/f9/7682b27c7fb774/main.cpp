#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

bool Pentagon(const int number) {
    const int numberShift = floor((std::sqrt(1.0 + 24 * number) + 1) / 6);
    return ((std::sqrt(1.0 + 24 * number) + 1) / 6 - numberShift) < std::numeric_limits<double>::epsilon();
}
int Sieve(const int number) {
    return number * (3 * number - 1) / 2;
}

int main() {
    int solution = 0;

    const int max = 10000;
    int pentagons[max];

    for(int i = 1; i < max; ++i) {
        pentagons[i] = Sieve(i);

        for(int j = i; j > 1; j--) {
            const int subtraction = pentagons[i] - pentagons[j];
            const int sum = pentagons[i] + pentagons[j];

            if(Pentagon(subtraction) && Pentagon(sum)) {
                solution = subtraction;
            }
        }
    }

    std::cout << "Solution: " << solution << std::endl;
}