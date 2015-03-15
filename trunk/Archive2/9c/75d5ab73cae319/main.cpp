#include <list>
#include <algorithm>

int main() {
    using waveElem = int;
    std::list<waveElem> waveFront;
    std::make_heap (waveFront.begin(), waveFront.end());
}