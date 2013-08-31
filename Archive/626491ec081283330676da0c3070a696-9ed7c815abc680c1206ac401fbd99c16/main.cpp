
enum color_enum {red, green, blue};
struct color_type {
    color_type() :diffuseColor(){}
    float diffuseColor[3];
    float& operator[](color_enum v) {return diffuseColor[v];}
    const float& operator[](color_enum v)const {return diffuseColor[v];}
};
struct Texture
{
        color_type color;
};

int main() {
    Texture myTexture;
    myTexture.color[red] = 1.0f;
}