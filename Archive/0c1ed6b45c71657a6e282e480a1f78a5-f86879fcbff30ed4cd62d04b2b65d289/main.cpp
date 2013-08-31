#include <iostream>

union Vector3
{
    double a[3];
    struct  
    {
        /// X component of the Vector3
        double x;
        /// Y component of the Vector3
        double y;
        /// Z component of the Vector3
        double z;
    };
};


const Vector3 Vector3Origin = 
{
    {0.0, 0.0, 0.0}    
};


int main()
{

}