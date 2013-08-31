
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

int main() {
    Texture myTexture;
    myTexture.color.r = 1.0f;
}