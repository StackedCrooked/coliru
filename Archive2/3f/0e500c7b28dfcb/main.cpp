#include <iostream>
#include <chrono>

#define CHRONO_TIMEPOINT            std::chrono::high_resolution_clock::time_point
#define CHRONO_NOW                  std::chrono::high_resolution_clock::now()
#define CHRONO_DIFF(_begin, _end)   std::chrono::duration_cast<std::chrono::duration<double>>(_end - _begin).count()

int main()
{
    auto _wait = [](const CHRONO_TIMEPOINT& x) {
        while(CHRONO_DIFF(x, CHRONO_NOW) < 1.0) {}
        return true;
    };
    auto start = CHRONO_NOW;
    _wait(CHRONO_NOW);
    auto end = CHRONO_NOW;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
}
