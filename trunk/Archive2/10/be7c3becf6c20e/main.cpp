#include <algorithm>

int main(int, char** argv) {
    float a[] = { (float)argv[0][0], (float)argv[0][1], (float)argv[0][2], (float)argv[0][2] };
    float b[4];
    
    std::transform(a, a+4, b, [](float x) { return 2*x; });
    
    return b[0] + b[1] + b[2] + b[3];
}