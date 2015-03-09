typedef double (*Function_ptr)(double);

const unsigned intervals_count = 1000;

double trapeze_method(Function_ptr f, double a, double b)
{
    const double dx = (a + b) / intervals_count;
    double result = 0;
    double interval_left = a;
    double interval_right = a + dx;
    for (unsigned i = 0; i < intervals_count; ++i) {
        result += dx * (f(interval_left) + f(interval_right)) / 2;
        interval_left = interval_right;
        interval_right += dx;
    }
    return result;
}

double rectangle_method(Function_ptr f, double a, double b)
{
    const double dx = (a + b) / intervals_count;
    double result = 0;
    double interval_left = a;
    double interval_right = a + dx;
    for (unsigned i = 0; i < intervals_count; ++i) {
        const double interval_middle = (interval_left + interval_right) / 2;
        result += dx * f(interval_middle);
        interval_left = interval_right;
        interval_right += dx;
    }
    return result;
}

double simpson_method(Function_ptr f, double a, double b)
{
    const double dx = (a + b) / intervals_count;
    double result = 0;
    double interval_left = a;
    double interval_right = a + dx;
    for (unsigned i = 0; i < intervals_count; ++i) {
        const double interval_middle = (interval_left + interval_right) / 2;
        result += (interval_right - interval_left) / 6 * (f(interval_left) + 4*f(interval_middle) + f(interval_right));
        interval_left = interval_right;
        interval_right += dx;
    }
    return result;
}

#include <iostream>
#include <iomanip>
using namespace std;

double f(double x)
{
    return x * x;
}

double integral_f(double x)
{
    return x * x * x / 3;
}

int main()
{
    cout << fixed << setprecision(10);
    const double a = 0;
    const double b = 3;
    cout << "Trapeze_method: " << trapeze_method(f, a, b) << '\n';
    cout << "Rectangle_method: " << rectangle_method(f, a, b) << '\n';
    cout << "Simpson_method: " << simpson_method(f, a, b) << '\n';
    cout << "Answer: " << integral_f(b) - integral_f(a) << '\n';
}