
struct Color {
    float r;
    float g;
    float b;
};
struct Texture
{
    union {
        Color color;
        float diffuseColor[3];
    };
        
};

#include <iostream>
int main() {
    Texture myTexture;
    myTexture.color.r = 1.0f;
    std::cout << myTexture.diffuseColor[0];
}