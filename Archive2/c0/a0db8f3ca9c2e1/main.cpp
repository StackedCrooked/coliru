#include <iostream>

class MinMax
{
private:
    int m_nMin;
    int m_nMax;

public:
    MinMax(int nMin, int nMax);

    int GetMin() { return m_nMin; }
    int GetMax() { return m_nMax; }

    friend MinMax operator+(const MinMax &cM1, const MinMax &cM2);
    friend MinMax operator+(const MinMax &cM, int nValue);
    friend MinMax operator+(int nValue, const MinMax &cM);
};

MinMax::MinMax(int nMin, int nMax)
{
    m_nMin = nMin;
    m_nMax = nMax;
}

MinMax operator+(const MinMax &cM1, const MinMax &cM2)
{
    //compare member variables to find minimum and maximum values between all 4
    int nMin = cM1.m_nMin < cM2.m_nMin ? cM1.m_nMin : cM2.m_nMin;
    int nMax = cM1.m_nMax > cM2.m_nMax ? cM1.m_nMax : cM2.m_nMax;

    //return a new MinMax object with above values
    return MinMax(nMin, nMax);
}

MinMax operator+(const MinMax &cM, int nValue)
{
    //compare member variables with integer value
    //to see if integer value is less or greater than any of them
    int nMin = cM.m_nMin < nValue ? cM.m_nMin : nValue;
    int nMax = cM.m_nMax > nValue ? cM.m_nMax : nValue;

    return MinMax(nMin, nMax);
}

MinMax operator+(int nValue, const MinMax &cM)
{
    //switch argument places and pass them to previous operator version
    //this avoids duplicate code by reusing function
    return (cM + nValue);
}


int main()
{
    MinMax cM1(10, 15);
    MinMax cM2(8, 11);
    MinMax cM3(3, 12);

    //sum all MinMax objects to find min and max values between all of them
    MinMax cMFinal = cM1 + 5 + 8 + cM2 + cM3 + 16;
    std::cout << cMFinal.GetMin() << ", " << cMFinal.GetMax() << std::endl;

    return 0;
}