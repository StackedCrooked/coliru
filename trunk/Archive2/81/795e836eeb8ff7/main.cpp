#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <limits>
#include <tuple>
#include <cstdio>
#include <iomanip>
#include <ios>
#include <array>
#include <type_traits>

 struct BasicCellData
{
    float min_height;
    float max_height;
    float avg_height;
    unsigned int num_updates;

    void reset()
    {
        min_height = max_height = avg_height = 0.0f;
        num_updates = 0;
    }

    void update( float height_above_ground )
    {
        if ( height_above_ground < min_height )
            min_height = height_above_ground;
        if ( height_above_ground > max_height )
            max_height = height_above_ground;
    }
};

struct HeightAdditionalData
{
    BasicCellData
        
    void update( float height_above_ground )
    {
        
    }
};

int main()
{
    std::cout << std::is_pod< BasicCellData >::value << std::endl;
 
}
