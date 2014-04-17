#include <iostream>
#include <iomanip>
#include <memory>
#include <cstdint>
#include <cmath>
 
int main()
{
    const double radius_meter = 6378137;
    const double world_width_meter = M_PI*radius_meter;
    int_fast64_t worldsize = 1L << 62;
    double pos_x = 854874.356004 / world_width_meter;
    double pos_y = 6712504.21593 / world_width_meter;
    int_fast64_t pixel_x = pos_x * worldsize;
    int_fast64_t pixel_y = pos_y * worldsize;
    
    std::cout << std::setprecision(15) << pos_x <<" "<< pos_y << std::endl;
    std::cout << std::setprecision(15) << pos_x * worldsize <<" "<< pos_y * worldsize << std::endl;
    std::cout << std::setprecision(15) << pixel_x <<" "<< pixel_y << std::endl;
}