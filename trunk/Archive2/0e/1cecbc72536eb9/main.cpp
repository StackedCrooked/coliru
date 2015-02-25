#include <vector>
#include <cassert>
#include <iostream>
#include <iomanip>

int depth = 10;
int denominator = 1<<depth;
int half = denominator/2;
std::vector<double> values;

double F(int x) {
    assert(x>=0 && x<=denominator);
    if (values[x] < 0) {
        if (x <= half)
            values[x] = 0.25*F(x*2);
        else 
            values[x] = 0.25+0.75*F(2*x-denominator);
    }
    return values[x];
}

int main() {
    values.resize(denominator+1, -1);
    values[0] = 0.0;
    values[denominator] = 1.0;
        
    for(int numerator=0; numerator<=denominator; ++numerator)
        F(numerator);
        
    for(int numerator=0; numerator<=denominator; ++numerator)
        std::cout << std::setw(4) << numerator << '/' << denominator << " = " << values[numerator] << '\n';
}