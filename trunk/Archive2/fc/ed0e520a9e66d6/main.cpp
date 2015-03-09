#include <cstdio>

int main()
{
    float v = 0.f;
    for(int i=0; i<0xFFFFFFF; ++i)
    {
        if(static_cast<int>(v) != i)
        {
            printf("%d %f\n", i, v);
            break;
        }
        v += 1.f;
    }
    
    
    return 0;
}
