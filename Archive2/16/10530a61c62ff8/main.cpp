#include <cmath>
#include <cstdint>
#include <limits>
#include <iostream>

int main() {
    using namespace std;
    
    double test = 0.82004366063971901;
    uint32_t result = std::lround(test * std::numeric_limits<uint32_t>::max());

    //Start Screen Begin
    cout << test << " -> " << result;
    //Start Screen End
}