#include <utility>
#include <iostream>
#include <array> 
struct Default {
    int foo() const {return 1;}
};
 
#ifndef _countof
#define _countof(a) (sizeof(a)/sizeof(a[0])) 
#endif


struct CPoint
{
    long x;
    long y;
};

using SPOINT = CPoint;

typedef struct {
    SPOINT   nPt[4];
    short     nZ[4];
    short     nWi[2];
} SEGMEELEM;


struct NonDefault {
    NonDefault(const NonDefault&) {}
    int foo() const {return 1;}
};
template <class TTobi>
class Tobi
{
    public:
    const std::array<CPoint, _countof(std::declval<SEGMEELEM>().nPt)> CalculatePoints() const
    {
        std::array<CPoint, _countof(std::declval<SEGMEELEM>().nPt)> afds;
        return afds;
    }
};

int main()
{
    std::array<CPoint, 4> asdf;
    std::array<CPoint, _countof(SEGMEELEM::nPt)> fdas;
    std::cout <<asdf.size()<< '\n';
    std::cout <<fdas.size()<< '\n';
    Tobi<int> tob;
    const auto Auto = tob.CalculatePoints();
    std::cout <<Auto.size()<< '\n';
    decltype(Default().foo()) n1 = 1; // int n1
//  decltype(NonDefault().foo()) n2 = n1; // will not compile
    decltype(std::declval<NonDefault>().foo()) n2 = n1; // int n2
    std::cout << "n2 = " << n2 << '\n';
}