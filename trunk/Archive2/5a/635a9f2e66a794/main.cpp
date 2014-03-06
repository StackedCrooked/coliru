#include  <iostream>

int main()
{
    float a = 1000;                                                                                                            

    if (a < 0 || a > 1000.f) // or (a < (float)0 || a > (float) 1000)
    {
        std::cout << " Hello world"  << std::endl;
    }
}