#include <iostream>

struct RGB 
{
    // this one assigns the value correctly
    RGB operator=(const int hex)
    {
        this->r = (hex>>16 & 0xFF) / 255.0f;
        this->g = (hex>>8  & 0xFF) / 255.0f;
        this->b = (hex     & 0xFF) / 255.0f;
        return *this;
    }
    //--------------------------------------------------------------------------------------
    // also works
    bool operator==(const RGB &color)
    {
        return (r == color.r && g == color.g && b == color.b);
    }
    // this is evil
    bool operator==(const int hex)
    {
        float rr = (hex>>16 & 0xFF) / 255.0f;
        float gg = (hex>>8  & 0xFF) / 255.0f;
        float bb = (hex     & 0xFF) / 255.0f;
    
        return (r == rr &&
                g == gg &&
                b == bb);
    }
    
    float r = 0, g = 0, b = 0;
};

int main()
{
    RGB a;
    a = 0x555555;
    bool equals = (a == 0x555555);
    
    std::cout << equals;
}
