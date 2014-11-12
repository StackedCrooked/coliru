#include <iostream>
#include <math.h>


void toHSI(float R, float G, float B, float& H, float& S, float& I) {
    I = (R+G+B)/3;
    if (I == 0)
    {
        S = 0;
    }
    else
    {
        float fl = fmin(R, G);
        fl = fmin(fl, B);
        S = 1-(fl/I);
    }
    float func = (R-(G/2.0)-(B/2.0))/sqrt((R*R)+(G*G)+(B*B)-(R*G)-(R*B)-(G*B));
    if (R==G && G == B)
    {
        H = 0;
        S = 0;
    }
    else if (G<B)
    {
        H = 360-(acos(func)*180.0/3.14159265);
    }
    else
    {
        H = acos(func)*180.0/3.1459265;
    }
}

void toRGB(float H, float S, float I, float& R, float& G, float& B) {
    if (H == 0)
    {
        R = I+2*I*S;
        G = I-I*S;
        B = I-I*S;
    }
    else if (H < 120)
    {
        float func = cos(H*3.14159265/180)/cos(60-H*3.14159265/180);
        R = I+I*S*func;
        G = I+I*S*(1-func);
        B = I-I*S;
    }
    else if (H == 120)
    {
        R = I-I*S;
        G = I+2*I*S;
        B = I-I*S;
    }
    else if (H < 240)
    {
        float func = cos((H-120)*3.14159265/180)/cos((180-H)*3.1459265/180);
        R = I-I*S;
        G = I+I*S*func;
        B = I+I*S*(1-func);
    }
    else if (H == 240)
    {
        R = I-I*S;
        G = I-I*S;
        B = I+2*I*S;
    }
    else
    {
        float func = cos((H-240)*3.14159265/180)/cos((300-H)*3.14159265/180);
        R = I+I*S*(1-func);
        G = I-I*S;
        B = I+I*S*func;
    }
}

int main() {
    int cnt = 0;
    for (int r = 0; r < 255; r += 10) {
        for (int g = 0; g < 255; g += 10) {
            for (int b = 0; b < 255; b += 10) {
                float r1, g1, b1, h, s, i;
                toHSI(r, g, b, h, s, i);
                toRGB(h, s, i, r1, g1, b1);
                if (fabs(r - r1) > 5 || fabs(g - g1) > 5 || fabs(b - b1) > 5) {
                    std::cout << r << ' ' << g << ' ' << b << " --> "
                        << h << ' ' << s << ' ' << i << " --> "
                        << r1 << ' ' << g1 << ' ' << b1 << std::endl;
                    if (++cnt > 100)
                        return 0;
                }
            }
        }
    }
}