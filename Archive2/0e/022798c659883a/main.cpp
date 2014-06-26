#include <iostream>
#include <limits>
#include <math.h>
#include <chrono>

void doubleTest(int loop)
{
    printf("double: \n");
    for (int i = 0; i < loop; i++)
    {
        double a = 1000.0, b = 45.0, c = 12000.0, d = 2.0, e = 7.0, f = 1024.0;
        a = sin(a);
        b = asin(b);
        c = sqrt(c);
        d = d + d - d + d;
        e = e * e + e * e;
        f = f / f / f / f / f;
    }
}

void floatTest(int loop)
{
    printf("float: \n");
    for (int i = 0; i < loop; i++)
    {
        float a = 1000.0f, b = 45.0f, c = 12000.0f, d = 2.0f, e = 7.0f, f = 1024.0f;
        a = (float) sin(a);
        b = (float) asin(b);
        c = (float) sqrt(c);
        d = d + d - d + d;
        e = e * e + e * e;
        f = f / f / f / f / f;
    }
}

void ftest()
{
    {
        std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
        doubleTest(5 * 10000000);
        std::chrono::steady_clock::time_point dTime = std::chrono::steady_clock::now();
        
        unsigned int ms = std::chrono::duration_cast<std::chrono::milliseconds>(dTime - time).count();
        printf("%u ms\n", ms);
    }

    {
        std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
        floatTest(5 * 10000000);
        std::chrono::steady_clock::time_point dTime = std::chrono::steady_clock::now();

        unsigned int ms = std::chrono::duration_cast<std::chrono::milliseconds>(dTime - time).count();
        printf("%u ms\n", ms);
    }
}

int main()
{
    /*
    float e = std::numeric_limits<float>::epsilon();
    float e2 = 1.0f / 8388608.0f;
    std::cout << "e       = " << e << "\n";
    std::cout << "log(e)  = " << log(e) / log(2) << "\n";
    std::cout << "e2      = " << e2 << "\n";
    std::cout << "log(e2) = " << log(e2) / log(2) << "\n";
    */
    ftest();
}