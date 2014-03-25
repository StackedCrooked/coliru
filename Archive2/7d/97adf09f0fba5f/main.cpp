#include <iostream>
#include <string>
#include <vector>
#include <cmath>

int main()
{
    const int max = 255;
    const float a = 0.055f;
    
    for (int c_int = 0; c_int <= max; ++c_int) {
        const float c = static_cast<float>(c_int) / max;
        const float c_22 = powf(c, 2.2f);
        float c_srgb;
        if (c <= 0.04045f) {
            c_srgb = c / 12.92f;
        } else {
            float ca = (c + a) / (1 + a);
            c_srgb = powf(ca, 2.4f);
        }
        
        int diff = abs(static_cast<int>(c_22 * max - c_srgb * max));
        if (diff > 1) {
            printf("%i, %i\n", c_int, static_cast<int>(c_22 * max - c_srgb * max));
        }
    }
    
    printf("\n");
    
    for (int c_int = 0; c_int <= max; ++c_int) {
        const float c = static_cast<float>(c_int) / max;
        const float c_22 = powf(c, 1.f/2.2f);
        float c_srgb;
        if (c <= 0.0031308) {
            c_srgb = c * 12.92f;
        } else {
            c_srgb = (1 + a) * powf(c, 1.f/2.4f) - a;
        }
        
        int diff = abs(static_cast<int>(c_22 * max - c_srgb * max));
        if (diff > 1) {
            printf("%i, %i\n", c_int, static_cast<int>(c_22 * max - c_srgb * max));
        }
    }
}