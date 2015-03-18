#include <iostream>
#include <bitset>
#include <math.h>

using namespace std;

float minv = 3.44f;
float maxv = 126.96f;
const int N = 9;

float u0 = 3.1f;
float u1 = -1.6f;
float u2 = 7.1f;

struct _stData
{
    void stData() { t = 0; U = 0; Uds = 0; dU = 0; level10 = 0; }
    void show() { cout << "t = " << t << ", U(t) = " << U << ", Ud = " << Uds << ", dU = " << dU << ", level10 = " << level10 << ", level2 " << (std::bitset<N>)level10 <<  endl; }
    float t;
    float U;
    float Uds;
    float dU;
    int level10;
} stData[5];

float f(float t)
{
    return u0 + u1 * t + u2 * t * t;
}

int main()
{
    float step = (maxv - minv) * pow(2, -N);
    float error = 0.0f;
    for(int i(0); i<5; i++)
    {
        stData[i].t = i;
        stData[i].U = f(i);
        
        float tmp_l = ( (stData[i].U - minv) / step);
        stData[i].level10 = round(tmp_l - 0.5);
        
        if(stData[i].level10 > pow(2, N) - 1)
            stData[i].level10 = pow(2, N) - 1;
            
        if(stData[i].level10 < 0)
            stData[i].level10 = 0;
        
        stData[i].Uds = stData[i].level10 * step + minv + 0.5 * step;
        stData[i].dU = stData[i].U - stData[i].Uds; //pow( pow(stData[i].U - stData[i].Uds, 2), 0.5);
        
        error += pow(stData[i].dU, 2);
        stData[i].show();
    }
    cout << "error " << pow(error/5, 0.5) << ", " << step * pow(12, -0.5) << endl;
    cout << "step " << step;
    return 0;
}