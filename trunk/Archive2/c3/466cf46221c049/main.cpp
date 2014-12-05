#include <cstdio>
#include <cmath>

void print(double ollaDeltaCqi)
{
    int cw0Sign         = (ollaDeltaCqi < 0) ? -1 : 1;
    int cw0OllaFraction = (ollaDeltaCqi*cw0Sign + .05 - static_cast<int>(ollaDeltaCqi)*cw0Sign) * 10;

    std::printf("ollaDeltaCqi = %f, OLLA delta=%d.%d\n", ollaDeltaCqi, static_cast<int>(ollaDeltaCqi), cw0OllaFraction);
}

void print2(double ollaDeltaCqi)
{
    int cw0Sign     = (ollaDeltaCqi < 0) ? 1 : 0;
    double intPart;
    double fracPart = std::abs(std::modf(ollaDeltaCqi, &intPart)) + 0.05;

    std::printf("ollaDeltaCqi = %f, OLLA delta=%c%d.%d\n", 
        ollaDeltaCqi, 
        static_cast<int>(cw0Sign ? '-' : '+'), 
        static_cast<int>(std::abs(intPart)), 
        static_cast<int>(fracPart * 10));
}

int main()
{
    print(0.580000);    // desired output = 0.6
    print(-0.580000);   // desired output = -0.6 -- doesn't work
    print(1.580000);    // desired output = 1.6
    print(-1.580000);   // desired output = -1.6
    
    printf("---------------\n");   
    
    print2(0.580000);
    print2(-0.580000);
    print2(1.580000);
    print2(-1.580000);
}
