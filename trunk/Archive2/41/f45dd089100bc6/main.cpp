enum InstructionSetEnum {InstructionsNormal, InstructionsAVX};

template<InstructionSetEnum e, typename T>
int RtDouble(T number)
{
    // Side effect: generates avx instructions
    const int N = 1000;
    float a[N], b[N];
    for (int n = 0; n < N; ++n)
    {
        a[n] = b[n] * b[n] * b[n];
    }    
    return number * 2;
}

/*  File: fn_normal.cpp */
//#include "fn_normal.h"
//#include "double.h"

int FnNormal(int num)
{
    return RtDouble<InstructionsNormal>(num);
}

/*  File: fn_avx.cpp */
//#include "fn_avx.h"
//#include "double.h"

int FnAVX(int num)
{
    return RtDouble<InstructionsAVX>(num);
}