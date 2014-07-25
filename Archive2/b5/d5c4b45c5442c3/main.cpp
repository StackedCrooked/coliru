#include <array>
#include <vector>
#include <iostream>

template<typename Geometry=void, typename Enable = void>
struct tag 
{
    typedef void type;
};

struct point_tag {}; 
struct triangle_tag {}; 

template<>
struct tag<std::vector<double>>
{
    typedef point_tag type; 
};

template<typename Point>
using triangle = 
typename std::enable_if
<
    std::is_base_of<typename tag<Point>::type, point_tag>::value,
    std::array<Point,3>
>::type;
// This works, but there is no restriction on Point to be tagged with point_tag.
//std::array<Point, 3>;

template <typename Point>
struct tag<triangle<Point>>  
{
    typedef triangle_tag type;
};

using namespace std;

int main(int argc, const char *argv[])
{
    typedef vector<double> pointType; 
    typedef triangle<pointType> triangleType;

    triangleType t = { { {0,0,0}, {1,0,0}, {0, 1,0} } }; 

    return 0;
}




