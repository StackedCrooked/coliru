#include <iostream>
#include <bitset>
#include <math.h>

using namespace std;

float minv = -32.89;
float maxv = 5.52;
int N = 14;

float u0 = 4.8f;
float u1 = 1.0f;
float u2 = -2.4f;

struct _stData
{
    void stData() { t = 0; U = 0; Uds = 0; dU = 0; level10 = 0; }
    void show() { cout << "t = " << t << ", U = " << U << ", Uds = " << Uds << ", dU = " << dU << ", level10 = " << level10 << ", level2 " << (std::bitset<14>)level10 <<  endl; }
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
        
        float tmp_l = ( (stData[i].U - minv) / step - 0.5);
        stData[i].level10 = round(tmp_l);
        
        stData[i].Uds =  stData[i].level10 * step + minv;
        stData[i].dU =  stData[i].U -  stData[i].Uds;
        
        error += pow(stData[i].dU, 2) * 0.2;
        stData[i].show();
    }

    cout << "error " << pow(error, 0.5) << ", " << step * pow(12, -0.5);
}
