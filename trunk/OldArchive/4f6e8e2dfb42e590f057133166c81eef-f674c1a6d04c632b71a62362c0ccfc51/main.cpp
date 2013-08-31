#define _USE_MATH_DEFINES
#include <cmath>


struct radians {
    radians() : value() {}
    explicit radians(double newval) :value(in_range(newval)) {}
    operator double() {return value;}
    radians& operator+=(radians rhs) {value=in_range(value+rhs.value); return *this;}
    radians& operator-=(radians rhs) {value=in_range(value-rhs.value); return *this;}
    radians& operator*=(double rhs) {value=in_range(value*value); return *this;}
    radians& operator/=(double rhs) {value=in_range(value/value); return *this;}
private:
    static double in_range(double value) {
        if (value<0) {
            unsigned div = unsigned(value/-(2*M_PI))+1;
            value += (div*2.0*M_PI);
        } else if (value>=2*M_PI) {
            unsigned div = unsigned(value/(2*M_PI));
            value -= (div*2.0*M_PI);
        }   
        return value;
    }
    double value;
};
radians operator+(radians lhs, radians rhs) {return lhs+=rhs;}
radians operator-(radians lhs, radians rhs) {return lhs-=rhs;}
radians operator*(radians lhs, double rhs) {return lhs*=rhs;}
radians operator/(radians lhs, double rhs) {return lhs/=rhs;}
radians rad_from_degree(double degrees) {return radians(degrees*2*M_PI/360.0);}


#include <iostream>
int main() {
    radians xrot(0); //use a units class
    radians rot_per_second = rad_from_degree(10);
    double time_passed = 0.1;
    radians rotate_thistime = rot_per_second * time_passed;
    xrot += rotate_thistime;
    
    std::cout << "zero+:" << radians(12.5664) << '\n'; //slightly more than 4PI
    std::cout << "2PI- :" << radians(12.5663) << '\n'; //slightly less than 4PI
    std::cout << "PI+  :" << radians(9.42478) << '\n'; //slightly more than 3PI
    std::cout << "PI-  :" << radians(9.42477) << '\n'; //slightly less than 3PI
    std::cout << "zero+:" << radians(6.28319) << '\n'; //slightly more than 2PI
    std::cout << "2PI- :" << radians(6.28318) << '\n'; //slightly less than 2PI
    std::cout << "PI+  :" << radians(3.14160) << '\n'; //slightly more than PI
    std::cout << "PI-  :" << radians(3.14159) << '\n'; //slightly less than PI
    std::cout << "zero+:" << radians(0.00001) << '\n'; //slightly more than zero
    std::cout << "zero :" << radians(0) << '\n';
    std::cout << "2PI- :" << radians(-0.00001) << '\n'; //slightly more than zero
    std::cout << "PI-  :" << radians(-3.14159) << '\n'; //slightly less than -PI
    std::cout << "PI-  :" << radians(-3.14160) << '\n'; //slightly more than -PI
    std::cout << "zero+:" << radians(-6.28318) << '\n'; //slightly less than -2PI
    std::cout << "2PI- :" << radians(-6.28319) << '\n'; //slightly more than -2PI
    std::cout << "PI+  :" << radians(-9.42477) << '\n'; //slightly less than -3PI
    std::cout << "PI-  :" << radians(-9.42478) << '\n'; //slightly more than -3PI
    std::cout << "zero+:" << radians(-12.5663) << '\n'; //slightly less than -4PI
    std::cout << "2PI- :" << radians(-12.5664) << '\n'; //slightly more than -4PI
}