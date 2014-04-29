#include <vector>
#include <type_traits>
#include <iostream>

using namespace std;

void GS(float x, float y, int xOff, int yOff, char f = 0x00){ cout << 1 << endl;}
template<class = void>
void GS(float x, float y, int xOff, int yOff, int maxW = -1, int maxH = -1, char f = 0x00){ cout << 2 << endl;}

int main(int argc, const char * argv[])
{
    GS(1,2,3,4);
    GS(1,2,3,4,char{});
    GS(1,2,3,4,2);
    
    return 0;
}