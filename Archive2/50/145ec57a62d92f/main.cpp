#include <iostream>


bool USER_AREATYPE_COMPARE(int area, int query)
{
    if ( (area & ~query) == 0 && (area & query) != 0)
        return true;
        
    return false;
}

int main()
{
    int TypePave = 0x01;
    int TypeGrass = 0x02;
    int TypeFire = 0x04;
    
    
    int Pedestrian = 0x03;
    int Bicycle =  0x01;
    int FireFighter = 0x07;
    
    //int AreaTypeAll = 0x00;
    
    std::cout << USER_AREATYPE_COMPARE(TypeGrass, Pedestrian) << std::endl;
    std::cout << USER_AREATYPE_COMPARE(TypePave, Pedestrian) << std::endl;
    std::cout << USER_AREATYPE_COMPARE(TypeFire | TypeGrass, Pedestrian) << std::endl;
    

    TypeGrass = 0x06;
    TypePave = 0x04;
    TypeFire = 0x03;
    Pedestrian = 0x01;
    Bicycle =  0x02;
    FireFighter = 0x07;
}