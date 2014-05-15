#include <iostream>
#include <time.h>

int main()
{
    const double Interval = static_cast<double>(1 * CLOCKS_PER_SEC);

    clock_t now;
    clock_t delta = clock();
    auto elapsed = .0;

    while (42) {
        now = clock();
        elapsed += static_cast<double>(now - delta);
        delta = now;

        if (elapsed > Interval) {
            elapsed -= Interval;
            std::cout << "Tick!\n";
        }
    }

    return 0;
}