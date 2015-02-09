struct Position_pod {
    int x,y,z;
};

class Position {
public:
    Position(int x=0, int y=0, int z=0):x(x),y(y),z(z){}
    int x,y,z;
};

struct text_descriptor {
    int             id;
    Position_pod    pos;
    const int       &constNum;
};

struct text_descriptor td[3] = {
     {0, {465,223}, 123},
     {1, {465,262}, 123},
};

int main() 
{
    return 0;
}