#include <iostream>
#include <cmath>
#include <cfloat>
 
int main() {
    std::cout<<"FP_NAN       = "<<FP_NAN      <<'\n';// 0
    std::cout<<"FP_INFINITE  = "<<FP_INFINITE <<'\n';// 1
    std::cout<<"FP_ZERO      = "<<FP_ZERO     <<'\n';// 2
    std::cout<<"FP_SUBNORMAL = "<<FP_SUBNORMAL<<'\n';// 3
    std::cout<<"FP_NORMAL    = "<<FP_NORMAL   <<'\n';// 4
    std::cout<<'\n';
    std::cout<<"std::fpclassify(NAN)         = "<<std::fpclassify(NAN)        <<'\n';
    std::cout<<"std::fpclassify(INFINITY)    = "<<std::fpclassify(INFINITY)   <<'\n';
    std::cout<<"std::fpclassify(0.f)         = "<<std::fpclassify(0.f)        <<'\n';
    std::cout<<"std::fpclassify(FLT_MIN/2.f) = "<<std::fpclassify(FLT_MIN/2.f)<<'\n';
    std::cout<<"std::fpclassify(1.f)         = "<<std::fpclassify(1.f)        <<'\n';
 
    return 0;
}