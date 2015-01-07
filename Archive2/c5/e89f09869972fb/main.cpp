#include <iostream>
#include <cstdarg>
#include <cmath>
 
double stddev(int count, ...) 
{
    double sum = 0;
    double sum_sq = 0;
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        double num = va_arg(args, double);
        sum += num;
        sum_sq += num*num;
    }
    va_end(args);
    return std::sqrt(sum_sq/count - (sum/count)*(sum/count));
}
 
int main() 
{
    std::cout << stddev(4, 25.0, 27.3, 26.9, 25.7) << '\n';
}