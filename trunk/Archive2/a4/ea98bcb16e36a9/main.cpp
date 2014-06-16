#include <algorithm>
#include <cstdint>


class Cube3x3
{
    union CornerData
    {
        std::uint8_t  mData8[8];
        std::uint16_t mData16[4];
        std::uint32_t mData32[2];
        std::uint64_t mData64;
    };

    union EdgeData
    {
        std::uint8_t  mData8[12];
        std::uint32_t mData32[3];
    };

    CornerData mCorners;
    EdgeData mEdges;

    static const Cube3x3 sSolved;
};


const Cube3x3 Cube3x3::sSolved = []{
    Cube3x3 cube;
    std::fill(std::begin(cube.mCorners.mData8), std::end(cube.mCorners.mData8), 0);
    std::fill(std::begin(cube.mEdges.mData8), std::end(cube.mEdges.mData8), 0);
    
    return cube;
}();


int main()
{
}
