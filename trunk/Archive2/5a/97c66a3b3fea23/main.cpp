#include <iostream>
#include <cstdarg>
#include <cmath>
 
double sample_stddev(int count, ...) 
{
    double sum = 0;
    va_list args1;
    va_start(args1, count);
    va_list args2;
    va_copy(args2, args1);
    for (int i = 0; i < count; ++i) {
        double num = va_arg(args1, double);
        sum += num;
    }
    va_end(args1);
    double mean = sum / count;
 
    double sum_sq_diff = 0;
    for (int i = 0; i < count; ++i) {
        double num = va_arg(args2, double);
        sum_sq_diff += (num-mean) * (num-mean);
    }
    va_end(args2);
    return std::sqrt(sum_sq_diff / count);
}
 
int main() 
{
    std::cout << sample_stddev(4, 25.0, 27.3, 26.9, 25.7) << '\n';
}