#include <cstdint>
class A
{

template<typename T>
using ptr = T*;

using ubyte = uint8_t;

public:

    const ptr<ubyte>
    getColor1() const {
        return &colors[0];
    }

    const ubyte*
    getColor2() const {
        return &colors[0];
    }


private:

    ubyte colors[4];
};

int main()
{
    
}