#include <iostream>
using namespace std;

struct object
{
    double  Latitude;   // degrees
    double  Longitude;  // degrees
    double  Altitude;   // feet   
    double  Pitch;      // degrees
    double  Bank;       // degrees
    double  Heading;    // degrees
    int   OnGround;   // 1=force to be on the ground
    int   Airspeed;   // knots
    
    int lightStrobe;                 //!< Is strobe light on?
    int lightLanding;                //!< Is landing light on?
    int lightBeacon;                 //!< Is beacon light on?
    int lightNav;                    //!< Is nav light on?
    int lightLogo;                   //!< Is logo light on?
    double flapsLeadingEdgeLeftPercent;       //!< Leading edge left in percent
    double flapsLeadingEdgeRightPercent;      //!< Leading edge right in percent
    double flapsTrailingEdgeLeftPercent;      //!< Trailing edge left in percent
    double flapsTrailingEdgeRightPercent;     //!< Trailing edge right in percent


    int engine1Combustion; //!< Engine 1 combustion flag
    int engine2Combustion; //!< Engine 2 combustion flag
    int engine3Combustion; //!< Engine 3 combustion flag
    int engine4Combustion; //!< Engine 4 combustion flag

    int gearHandlePosition;          //!< Gear handle position
};

int main() {
	std::cout << "sizeof: " << sizeof(object) << std::endl;
    std::cout << "sum: " << 10 * sizeof(double) + 12 * sizeof(int) << std::endl;
	// your code goes here
	return 0;
}