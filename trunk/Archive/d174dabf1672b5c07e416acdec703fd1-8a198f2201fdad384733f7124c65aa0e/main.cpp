#include <algorithm>

struct rgb {
    char red;
    char green;
    char blue;
};
rgb* mPtr(unsigned,unsigned){return NULL;}

void mFillHLine( rgb& uRGB, unsigned uX, unsigned uY, unsigned uW )
{
    if ( uW > 0 )
    {
        rgb* pvPixel = mPtr( uX, uY );
        std::fill(pvPixel, pvPixel + uW*3, uRGB);
    }
}

int main() {
}