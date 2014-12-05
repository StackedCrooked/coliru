#include <cstdio>

void print(double ollaDeltaCqi)
{
    int cw0Sign         = (ollaDeltaCqi < 0) ? -1 : 1;
    int cw0OllaFraction = (ollaDeltaCqi*cw0Sign + .05 - static_cast<int>(ollaDeltaCqi)*cw0Sign) * 10;

    std::printf("ollaDeltaCqi = %f, OLLA delta=%d.%d\n", ollaDeltaCqi, static_cast<int>(ollaDeltaCqi), cw0OllaFraction);
}

int main()
{
    print(0.580000);    // desired output = 0.6
    print(-0.580000);   // desired output = -0.6 -- doesn't work
    print(1.580000);    // desired output = 1.6
    print(-1.580000);   // desired output = -1.6
}
