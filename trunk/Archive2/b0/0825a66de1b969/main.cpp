    #include <iostream>
    #include <cmath>
    #include <boost/math/constants/constants.hpp>
    
    double piFunc() { return std::atan(1)*4; }
    
    int main()
    {
        double pi = M_PI;
        std::cout << pi << std::endl;
        std::cout << boost::math::constants::pi<double>() << std::endl ;
        std::cout << piFunc() << std::endl;
    }